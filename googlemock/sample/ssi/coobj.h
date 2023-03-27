/**
 * @brief		single CANopen object class
 * @details	
 * @author		inode(joongyoung.eom@endoquestrobotics.com)
 * @version		initial
 * @copyright	EndoQuest Robotics, Inc. All rights reserved.
 */

#ifndef __SSI_COOBJ_H__
#define __SSI_COOBJ_H__

#include <cstdint>
#include <cstddef>
#include <cstdlib>

#include <stdexcept>

#include <ssi/comst.h>

namespace ssi
{
	// forward decl
	template <typename T> class copdo;
	template <typename T> class cosdo;
	class coraw;

	/**
	 * abstract class of single CANopen object
	 * TODO:'
	 *  i believe that this class would be better to inherit std::atomic<T>.
	 *  another classes like monitors, loggers and communication modules can access the value
	 *  via same interface with FSM's another variables then.
	 */
	template <typename T>
	class coobj
	{
		friend class copdo<T>;
		friend class cosdo<T>;
		friend class coraw;

	public:
		typedef T					value_type;
		typedef uint16_t			slvid_type;
		typedef uint16_t			index_type;
		typedef uint8_t				subindex_type;

		enum flag_t {
			rdonly = 0x01,
			wronly = 0x02,
			rdwr = 0x03
		};

		enum type_t {
			boolean = 0x0001,
			integer8 = 0x0002,
			integer16 = 0x0003,
			integer64 = 0x0015,
			unsigned8 = 0x0005,
			unsigned16 = 0x006,
			unsigned32 = 0x0007,
			unsigned64 = 0x001b,
			real32 = 0x0008,
			real64 = 0x0011,
			visible_string = 0x0009,
			octet_string = 0x000a,
			domain = 0x000f
		};

		enum mapping_t {
			no = 0x00,
			yes = 0x01,
			txmap = 0x02,
			rxmap = 0x04,
			txrxmap = 0x06
		};

		explicit coobj(const index_type index = 0u, const subindex_type subindex = 0u, const flag_t flag = flag_t::rdwr, const mapping_t mapping = mapping_t::no, const T min = static_cast<T>(0), const T max = static_cast<T>(0), const T def = static_cast<T>(0)) :
			_mst(nullptr), _index(index), _subindex(subindex), _flag(flag), _mapping(mapping), _min(min), _max(max), _def(def) { }

		virtual ~coobj() { }

		index_type index() const { return _index; }

		subindex_type subindex() const { return _subindex; }

		T min() const { return _min; }
		T max() const { return _max; }
		T def() const { return _def; }

	protected:
		index_type _index;
		subindex_type _subindex;
		flag_t _flag;
		type_t _type;
		mapping_t _mapping;
		T _min;
		T _max;
		T _def;

		comst* _mst;

		/**
		 * assigning _mst is allowed to child classes only
		 */
		explicit coobj(comst* mst, const index_type index = 0u, const subindex_type subindex = 0u, const flag_t flag = flag_t::rdwr, const mapping_t mapping = mapping_t::no, const T min = static_cast<T>(0), const T max = static_cast<T>(0), const T def = static_cast<T>(0)) :
			_mst(mst), _index(index), _subindex(subindex), _flag(flag), _mapping(mapping), _min(min), _max(max), _def(def) { }
	};

	/**
	 * PDO class
	 * the only allowed way to read and write PDO is to access process images via class copi's interfaces
	 */
	template <typename T>
	class copdo : public coobj<T>
	{
	public: 
		using typename coobj<T>::value_type;
		using typename coobj<T>::index_type;
		using typename coobj<T>::subindex_type;

		// default constructor is disallowed
		copdo() = delete;

		copdo(comst& mst, comst::map_t map, const size_t bit_addr, const size_t bit_size = sizeof(T) * 8) :
			coobj<T>::coobj(&mst), _pi(map == comst::in ? mst.pin() : mst.pout()), _bit_addr(bit_addr), _bit_size(bit_size) { }

		~copdo() { }

		inline virtual T read() { return _mst->template readpdo<T>(_pi, _bit_addr); }

		inline virtual ssize_t write(T val) { return _mst->template writepdo<T>(_pi, _bit_addr, val); }

	private:
		copi& _pi;
		uint32_t _bit_addr;
		uint32_t _bit_size;
		using coobj<T>::_mst;
	};

	/**
	 * RAW interfacing class to the process images
	 * it provides the way to access aggregated PDO for digital I/O or something else(up to 64bits)
	 * and it's also probable to access specific field of PDO directly
	 */
	class coraw : public coobj<uint64_t>
	{
	public:
		// default constructor is disallowed
		coraw() = delete;

		/**
		 * constructor
		 * @exception		throws ssi::invalid_argument, when it's facing invalid bit_size
		 */
		coraw(comst& mst, comst::map_t map, const size_t bit_addr, const size_t bit_size) :
			coobj<uint64_t>::coobj(&mst), _pi(map == comst::in ? mst.pin() : mst.pout()), _bit_addr(bit_addr), _bit_size(bit_size) { }

		~coraw() { }

		inline ssize_t read(uint8_t *dst) { return _mst->readpdo(_pi, dst, _bit_addr, _bit_size); }
		inline ssize_t write(uint8_t *src) { return _mst->writepdo(_pi, src, _bit_addr, _bit_size); }

	private:
		copi& _pi;
		uint32_t _bit_addr;
		uint32_t _bit_size;
		using coobj<uint64_t>::_mst;
	};

	/**
	 * SDO class
	 * you can access SDO via ecatmst's API, and it can be blocked
	 */
	template <typename T>
	class cosdo : public coobj<T> {
	public:
		using typename coobj<T>::slvid_type;
		using typename coobj<T>::value_type;
		using typename coobj<T>::index_type;
		using typename coobj<T>::subindex_type;

		// default constructor is disallowed
		cosdo() = delete;

		cosdo(comst& mst, const slvid_type slvid, const coobj<T>& obj) :
			coobj<T>::coobj(&mst, obj._index, obj._subindex, obj._flag, obj._mapping, obj._min, obj._max, obj._def), _slvid(slvid) { }

		cosdo(comst& mst, const slvid_type slvid, const index_type index, const subindex_type subindex) :
			coobj<T>(&mst, index, subindex), _slvid(slvid) { }

		~cosdo() { }

		inline virtual T read() { return _mst->template readsdo<T>(_slvid, _index, _subindex); }

		inline virtual ssize_t write(const T val) { return _mst->template writesdo<T>(_slvid, _index, _subindex, val); }

	private:
		slvid_type _slvid;
		using coobj<T>::_mst;
		using coobj<T>::_index;
		using coobj<T>::_subindex;
	};
}

#endif // __SSI_COOBJ_H__
