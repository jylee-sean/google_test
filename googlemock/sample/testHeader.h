

#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include <mutex>
#include <memory>

namespace ccl
{
	namespace event
	{
		// forward decl
		template <typename T, bool THREAD_SAFE> class subject;
		
		struct base { };

		/**
		 * generic observer template
		 */
		template<typename T, typename E>
		class observer : std::enable_shared_from_this< observer<T, E> >
		{
			friend class subject<T, true>;
			friend class subject<T, false>;

		public:
			static constexpr bool is_thread_safe = false;
			
			observer() : std::enable_shared_from_this< observer<T, E> >::enable_shared_from_this(), _sbj(nullptr) { }

			virtual ~observer() { if(_sbj != nullptr) { _sbj->detach(*this); } }

			T* subject() const { return this->_sbj; }

		protected:
			/// subject calls this method by retrieving its all observers attached
			virtual void update(T& sbj, const E& e) = 0;

		private:
			T* _sbj;

			void link(T& sbj) { this->_sbj = &sbj; }

			void link(T* sbj) __attribute__((unused)) { if(sbj) this->_sbj = sbj; }

			void unlink() { this->_sbj = nullptr; }
		};

		/**
		 * generic subject template
		 */
		template <typename T, bool THREAD_SAFE = true>
		class subject
		{
		public:
			static constexpr bool is_thread_safe = THREAD_SAFE;

			subject() { }

			virtual ~subject() { }

			/**
			 * @warning		this method doesn't care of the duplicate entry
			 */
			template<typename E>
			void attach(observer<T, E> &o)
			{
				std::unique_lock<std::mutex> l(_lock, std::defer_lock);
				if(THREAD_SAFE) l.lock();
				objects<E>().push_back(&o);
				o.link(*static_cast<T*>(this));
			}

			template<typename E>
			void attach(observer<T, E> *o)
			{
				if(o) attach<E>(*o);
			}

			/// remove all observers from the list
			template<typename E>
			void detach()
			{
				while(!objects<E>().empty())
				{
					detach(*objects<E>().begin());
					// (void)objects<E>().erase(objects<E>().begin());
				}
			}

			/// remove the observer from the list
			template<typename E>
			void detach(observer<T, E> &o)
			{
				std::unique_lock<std::mutex> l(_lock, std::defer_lock);
				if(THREAD_SAFE) l.lock();
				for(typename std::vector<observer<T, E> *>::iterator i = objects<E>().begin(); i != objects<E>().end(); i++)
				{
					if(*i == &o)
					{
						o.unlink();
						objects<E>().erase(i);
						return ;
					}
				}
			}

			template<typename E>
			void detach(observer<T, E> *o)
			{
				if(o) detach<E>(*o);
			}

			template<typename E>
			void notify(const E& e = E{ })
			{
				std::unique_lock<std::mutex> l(_lock, std::defer_lock);
				if(THREAD_SAFE) l.lock();
				// for_each(objects<E>().begin(), objects<E>().end(), [&](observer<T, E> *o) { if(o && o->subject()) o->update(*static_cast<T*>(this), e); });
				for(auto o : objects<E>())
					if(o && (o->subject() == this)) o->update(*static_cast<T*>(this), e);
			}

		private:
			template<typename E>
			std::vector<observer<T, E>*>& objects() {
				static std::vector<observer<T, E>*> _objs;
				return _objs;
			}

			std::mutex _lock;
		};
	}
}

class copi
{
public:
		static constexpr size_t max_buf_size = 1510;
		enum access_t
		{
			mutex,
			nonex
		};
		copi(size_t size = 0, access_t mode = mutex) : _access(mode), _size(size), _ptr(nullptr) {
			(void)pthread_rwlock_init(&_rwlock, NULL);
			if(_size > max_buf_size) {
				throw std::runtime_error("invalid size"); }
			// this statement just assigns the pointer by using placement new
			_ptr = new (_buf) uint8_t[max_buf_size];
			//::syslog(LOG_NOTICE, " <notice> ssi::copi is created (%p,%d bytes)", _ptr, _size);
		}

		~copi() {
			if(_access == mutex) {
				(void)pthread_rwlock_destroy(&_rwlock); }
		}
		copi(copi const&) = delete;
		copi& operator=(copi const&) = delete;
	size_t size() const { return _size; }

		/**
		 * get the pointer to the process image data
		 * @warning		this is the direct interface to the process image
		 *				it may cause a memory synchronization problem without using rwlock API
		 * @return		always ptr to process image data
		 */
		uint8_t *pointer() const { return _ptr; }

		void wrlock() { if(_access == mutex) { (void)pthread_rwlock_wrlock(&_rwlock); } }
		void rdlock() { if(_access == mutex) { (void)pthread_rwlock_rdlock(&_rwlock); } }
		void unlock() { if(_access == mutex) { (void)pthread_rwlock_unlock(&_rwlock); } }

		/**
		 * change size of the process image
		 * @warning		this function doesn't allocate memory, just change its size of the static buffer
		 * @param		size number of bytes in the size changed
		 * @return		always size
		 * @exception	throws ssi::invalid_argument, if the function gets bigger size than max_buf_size
		 */
		size_t resize(const size_t size) {
			if(size > max_buf_size) {
				throw std::runtime_error("invalid size");
			}
			wrlock();
			_size = size;
			unlock();
			
			return _size;
		}

		/**
		 * read byte aligned raw data from the internal buffer
		 * @param		dst is ptr to load the data
		 * @param		bit_offset is the beginning of the range of elements to copy from
		 * @param		bit_size is number of bytes in the elements to copy
		 * @return		bit_size on success, 0 on error
		 */
		virtual ssize_t read(uint8_t* dst, size_t bit_offset, size_t bit_size) {
			if( (bit_offset & 0x07) != 0 || (bit_size & 0x07) !=0 )
				return 0;
			rdlock();
			std::memcpy(dst, _buf + (bit_offset >> 3), bit_size >> 3);
			unlock();
			return bit_size;
		}

		/**
		 * write byte aligned raw data to the internal buffer
		 * @param		src is ptr to read the data
		 * @param		bit_offset is the beginning of the range of elements to copy from
		 * @param		bit_size is number of bytes in the elements to copy
		 * @return		bit_size on success, 0 on error
		 */
		virtual ssize_t write(uint8_t* const src, size_t bit_offset, size_t bit_size) {
			if( (bit_offset & 0x07) != 0 || (bit_size & 0x07) !=0 )
				return 0;
			wrlock();
			std::memcpy(_buf + (bit_offset >> 3), src, bit_size >> 3);
			unlock();
			return bit_size;
		}

	protected:
		access_t _access;

		/// number of bytes in the image
		size_t _size;

		/// ptr to process image
		uint8_t *_ptr;

		/// pthread rwlock
		pthread_rwlock_t _rwlock;

	private:
		uint8_t _buf[max_buf_size];
};

class comst : public ccl::event::subject<comst>

{
	public:
	enum map_t { in, out };
	static constexpr uint16_t invalid_slave_id = std::numeric_limits<uint16_t>::max();

	class event : public ccl::event::base { };
	class sync_done : public ccl::event::base { };

	comst() {}
	virtual ~comst() {}


	virtual copi& pin() = 0;
	virtual copi& pout() = 0;

	virtual bool wait_for(size_t ncycles, std::chrono::steady_clock::duration timeout = std::chrono::microseconds(100000)) = 0;


	virtual ssize_t readpdo(copi& pi, uint8_t* dst, size_t bit_offset, size_t bit_size) = 0;	
	virtual ssize_t writepdo(copi& pi, uint8_t* const src, size_t bit_offset, size_t bit_size) = 0;

	template <typename T>
	inline T readpdo(copi& pi, const size_t bit_offset) try {
		T val = T(0);
		(void)readpdo(pi, reinterpret_cast<uint8_t*>(&val), bit_offset, std::is_same<T, bool>::value ? 1 : sizeof(T) * 8);
		return val;
	} catch(...) {
		throw;
	}

	template <typename T>
	inline T readpdo(const map_t map, const size_t bit_offset) try {
		T val = T(0);
		(void)readpdo( (map == comst::in) ? pin() : pout(), reinterpret_cast<uint8_t*>(&val), bit_offset, std::is_same<T, bool>::value ? 1 : sizeof(T) * 8 );
		return val;
	} catch(...) {
		throw;
	}

	template <typename T>
	inline ssize_t writepdo(copi& pi, const size_t bit_offset, T val) try {
		return writepdo(pi, reinterpret_cast<uint8_t*>(&val), bit_offset, std::is_same<T, bool>::value ? 1 : sizeof(T) * 8);
	} catch(...) {
		throw;
	}

	template <typename T>
	inline ssize_t writepdo(const map_t map, const size_t bit_offset, T val) try {
		return writepdo( (map == comst::in) ? pin() : pout(), reinterpret_cast<uint8_t*>(&val), bit_offset, std::is_same<T, bool>::value ? 1 : sizeof(T) * 8 );
	} catch(...) {
		throw;
	}


	virtual ssize_t readsdo(uint16_t slave_id, uint16_t index, uint8_t sub_index, uint8_t *dst, size_t bit_size) = 0;
	virtual ssize_t writesdo(uint16_t slave_id, uint16_t index, uint8_t sub_index, uint8_t *src, size_t bit_size) = 0;

	template <typename T>
	inline T readsdo(const uint16_t slave_id, const uint16_t index, const uint8_t sub_index) try {
		T val;
		readsdo(slave_id, index, sub_index, reinterpret_cast<uint8_t*>(&val), sizeof(val) * 8);
		return val;
	} catch(...) {
		throw;
	}


	template <typename T>
	ssize_t writesdo(const uint16_t slave_id, const uint16_t index, const uint8_t sub_index, T val) try {
		writesdo(slave_id, index, sub_index, reinterpret_cast<uint8_t*>(&val), sizeof(val) * 8);
		return static_cast<ssize_t>(sizeof(T) * 8);
	} catch(...) {
		throw;
	}

	private:

	virtual const char* _sync() = 0;
	virtual const char* _evnt() = 0;

	std::mutex _lock;	

};


class ecatmst : public comst
{
	public:

	virtual ssize_t readpdo(copi& pi, uint8_t* dst, size_t bit_offset, size_t bit_size) override
	{

		return 0;
	}
};