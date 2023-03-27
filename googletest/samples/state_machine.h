/**
 * @brief		generic state machine template class
 * @details		
 * @author		inode(joongyoung.eom@endoquestrobotics.com)
 * @version		initial
 * @copyright	EndoQuest Robotics, Inc. All rights reserved.
 */

#ifndef __CCL_STATE_MACHINE_H__
#define __CCL_STATE_MACHINE_H__

#if (__cplusplus < 201103L)
# error "c++11 is required"
#endif


namespace ccl
{
	template<typename T, typename ...E>
	class state_machine
	{
	public:
		// typedef void (T::*state_t)();
		using state_t = void (T::*)(E...);

		state_machine() : _from(nullptr), _prev(nullptr), _curr(nullptr) { }

		virtual ~state_machine() { }

		state_machine(state_machine const&) = delete;

		state_machine& operator=(state_machine const&) = delete;

		virtual void run() = 0;

		inline void step(E... args) {
			(static_cast<T*>(this)->*state())(args...);
		}
		
		inline const state_t from() const {
			return this->_from;
		}

		inline const state_t prev() const {
			return this->_prev;
		}
		 
		inline const state_t state() const {
			return this->_curr;
		}

		inline bool inloop() const {
			return this->_prev == this->_curr;
		}

		inline bool inloop(state_t s) const {
			return inloop() && state() == s;
		}
		
	protected:
		state_t _from;
		state_t _prev;
		state_t _curr;

		template<typename F>
		inline void once(F&& f) {
			if(_prev != _curr)
				f();
		}

		inline void transit(state_t next) {
			if(_curr != next)
				_from = _curr;
			this->_prev = this->_curr;
			this->_curr = next;
		}

		template<typename F>
		inline void transit(state_t next, F&& f) {
			if(next != _curr)
				f();
			transit(next);
		}
	};
}

/*
namespace experimental
{
	template<typename T, typename ...E>
	class state_machine
	{
	public:
		// typedef void (T::*state_t)();
		using addr_t = void (T::*)(E...);
		using state_t = std::function<void(T&, E...)>;

		state_machine() : _prev(nullptr), _curr(nullptr) {
			std::cout << "created from " << addr(_prev) << " to " << addr(_curr) << std::endl;
		}

		virtual ~state_machine() { }

		state_machine(state_machine const&) = delete;

		state_machine& operator=(state_machine const&) = delete;

		virtual void run() = 0;

		addr_t* addr(state_t f) {
			return f.template target<addr_t>();
		}

	protected:
		state_t _prev;
		state_t _curr;

		inline state_t prev() const {
			return this->_prev;
		}
		 
		inline state_t state() const {
			return this->_curr;
		}
		
		template<typename F>
		inline void once(F&& f) {
			if(addr(_prev) != addr(_curr))
				f();
		}

		inline void transit(state_t next) {
			this->_prev = this->_curr;
			this->_curr = next;
		}

		template<typename F>
		inline void transit(state_t next, F&& f) {
			if(addr(next) != addr(_curr))
				f();
			transit(next);
		}

		inline void reenter(state_t next) {
			this->_prev = nullptr;
			this->_curr = next;
		}
	};
}
*/

#endif // __CCL_STATE_MACHINE_H__
