/**
 * @brief		field bus master base class for CANopen interface
 * @detail		this header is based on EtherCAT master stack's structure
 *				it means that there always is a kind of process image to access PDO
 *				and another interfaces for reading / writing SDO
 * @author		inode(joongyoung.eom@endoquestrobotics.com)
 * @version		initial
 * @copyright	EndoQuest Robotics, Inc. All rights reserved.
 */

#ifndef __SSI_COMST_H__
#define __SSI_COMST_H__

#include <mutex>
#include <cassert>
#include <functional>

#include <ccl/event.h>
#include <ssi/copi.h>

namespace ssi
{
	class comst : public ccl::event::subject<comst>
	{
	public:
		enum map_t { in, out };
		static constexpr uint16_t invalid_slave_id = std::numeric_limits<uint16_t>::max();

		class event : public ccl::event::base { };
		class sync_done : public ccl::event::base { };

		comst() { }

		virtual ~comst() { }

		/// get the input process image to access data
		virtual copi& pin() = 0;

		/// get the input process image to access data
		virtual copi& pout() = 0;

		/**
		 * wait for master cycles
		 * @param		ncycles how many cycles you wanna wait for
		 * @param		timeout is time allowed until the operation is completed(100ms by default)
		 * @return		true on success, false on timeout
		 */
		virtual bool wait_for(size_t ncycles, std::chrono::steady_clock::duration timeout = std::chrono::microseconds(100000)) = 0;

		/**
		 * read a PDO
		 * @param		pi is the ptr of process image
		 * @param		dst is the ptr to read
		 * @param		bit_offset is object's bit offset on the process image
		 * @param		bit_size is number of bits in the data
		 * @return		number of bits read on success, others on fail
		 */
		virtual ssize_t readpdo(copi& pi, uint8_t* dst, size_t bit_offset, size_t bit_size) = 0;

		/**
		 * write a PDO
		 * @param		pi is the ptr of process image
		 * @param		dst is the ptr to write
		 * @param		bit_offset is object's bit offset on the process image
		 * @param		bit_size is number of bits in the data
		 * @return		number of bits written on success, others on fail
		 */
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

		/**
		 * read a SDO
		 * internal function to be implemented by inherited class
		 * @param		slave_id EtherCAT slave id
		 * @param		index CANopen object index to read
		 * @param		sub_index object sub index to read
		 * @param		dst ptr to read
		 * @param		bit_size is number of bits in the data
		 * @return		number of bits read on success, others on fail
		 */
		virtual ssize_t readsdo(uint16_t slave_id, uint16_t index, uint8_t sub_index, uint8_t *dst, size_t bit_size) = 0;

		/**
		 * write a SDO
		 * internal function to be implemented by inherited class
		 * @param		slave_id EtherCAT slave id
		 * @param		index is CANopen object index
		 * @param		sub_index is object sub index to write
		 * @param		src ptr to write
		 * @param		bit_size is number of bits in the data
		 * @return		number of bits written on success, others on fail
		 */
		virtual ssize_t writesdo(uint16_t slave_id, uint16_t index, uint8_t sub_index, uint8_t *src, size_t bit_size) = 0;

		/**
		 * read a SDO via CoE
		 * @param		slave_id EtherCAT slave id
		 * @param		index CANopen object index to read
		 * @param		sub_index object sub index to read
		 * @return		always value came from CoE communication
		 */
		template <typename T>
		inline T readsdo(const uint16_t slave_id, const uint16_t index, const uint8_t sub_index) try {
			T val;
			readsdo(slave_id, index, sub_index, reinterpret_cast<uint8_t*>(&val), sizeof(val) * 8);
			return val;
		} catch(...) {
			throw;
		}

		/**
		 * write a SDO via CoE
		 * @param		slave_id EtherCAT slave id
		 * @param		index CANopen object index to write
		 * @param		sub_index object sub index to write
		 * @return		always number of bits in val
		 */
		template <typename T>
		ssize_t writesdo(const uint16_t slave_id, const uint16_t index, const uint8_t sub_index, T val) try {
			writesdo(slave_id, index, sub_index, reinterpret_cast<uint8_t*>(&val), sizeof(val) * 8);
			return static_cast<ssize_t>(sizeof(T) * 8);
		} catch(...) {
			throw;
		}

	private:
		/**
		 * internal sync function
		 * i expect this function is called by master stack for every cycle
		 * and the implementation must contains updating it's process images and throw comst::sync_done
		 */
		virtual const char* _sync() = 0;

		/**
		 * internal event handler
		 * i expect this function is called by master implementation in case that some event occurs
		 * and the implementation must contains throwing comst::event
		 */
		virtual const char* _evnt() = 0;

		std::mutex _lock;
	};
}

#endif // _SSI_COMST_H__
