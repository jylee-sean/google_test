/**
 * @brief		class of single process image for CANopen master
 * @details		EtherCAT or USB based devices can refer its actual value via process images
 *				It's a single linear buffer based on C array
 *				Some communication base like KPA ethercat master can support this via their own API,
 *				But others like usbmst which i implemented mimic this feature
 *				Anyway, both must provide process images which can access data directly,
 *				and it means that they must include this class' instance as a member variable
 * @author		inode(joongyoung.eom@endoquestrobotics.com)
 * @version		initial
 * @copyright	EndoQuest Robotics, Inc. All rights reserved.
 */

#ifndef __SSI_COPI_H__
#define __SSI_COPI_H__

#include <cstdint>
#include <cstddef>
#include <cstdlib>

#include <ssi/exception.h>

#include <unistd.h>
#include <syslog.h>
#include <pthread.h>

namespace ssi
{
	class copi
	{
	public:
		static constexpr size_t max_buf_size = 1510;

		enum access_t
		{
			/**
			* mutual exclusive access
			* read() / write() synchronization is guranteed by this implementation based on pthread_rwlock
			*/
			mutex,

			/**
			* nonexeclusive access
			* do nothing for synchronization
			*/
			nonex
		};

		copi(size_t size = 0, access_t mode = mutex) : _access(mode), _size(size), _ptr(nullptr) {
			(void)pthread_rwlock_init(&_rwlock, NULL);
			if(_size > max_buf_size) {
				throw ssi::invalid_argument("invalid size"); }
			// this statement just assigns the pointer by using placement new
			_ptr = new (_buf) uint8_t[max_buf_size];
			::syslog(LOG_NOTICE, " <notice> ssi::copi is created (%p,%d bytes)", _ptr, _size);
		}

		~copi() {
			if(_access == mutex) {
				(void)pthread_rwlock_destroy(&_rwlock); }
		}

		// copy constructors are disallowed
		copi(copi const&) = delete;
		copi& operator=(copi const&) = delete;

		/**
		 * get number of bytes in the process image
		 * @return		always size which is passed from the constructor
		 */
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
				throw ssi::invalid_argument("invalid size");
			}
			wrlock();
			_size = size;
			unlock();
			::syslog(LOG_NOTICE, " <notice> ssi::copi is resized (%p,%d bytes)", _ptr, _size);
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
}

#endif // __SSI_COPI_H__
