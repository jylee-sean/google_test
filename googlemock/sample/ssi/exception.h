/**
 * @brief		SSI Software global error codes and exceptions classes
 * @details		
 * @author		inode(joongyoung.eom@endoquestrobotics.com)
 * @version		initial
 * @copyright	EndoQuest Robotics, Inc. All rights reserved.
 */

#ifndef __SSI_EXCEPTION_H__
#define __SSI_EXCEPTION_H__

#include <string>
#include <cstdint>
#include <cstddef>
#include <stdexcept>

#include <syslog.h>

namespace ssi
{
	class exception { };

	class no_error : public exception { };

	class logic_error : public exception { };
	
	/**
	 * defines a type of object to be thrown as an runtime exeption
	 * it reports generic runtime error
	 */
	class runtime_error : public ssi::exception
	{
	public:
		runtime_error(const char* w, const bool gen_log = true) noexcept : _what(w) {
			if(gen_log) ::syslog(LOG_ERR, " <error> runtime_error(%s) has been created", what().c_str());
		}
		runtime_error(const std::string& w, const bool gen_log = true) noexcept : runtime_error(w.c_str(), gen_log) { }
		virtual ~runtime_error() { }
		virtual const std::string& what() const noexcept { return this->_what; }

	private:
		const std::string _what;
	};

	/**
	 * defines a type of object to be thrown as a critical unrecoverable exception
	 */
	class critical_error : public ssi::runtime_error
	{
	public:
		using ssi::runtime_error::runtime_error;
		using ssi::runtime_error::what;
	};

	/**
	 * defines a type of object to be thrown as an exception.
	 * it reports exceptional cases of ecatmst API came from KPA EtherCAT master stack mostly
	 */
	class ecat_error : public ssi::runtime_error
	{
	public:
		ecat_error(const char* const w, const int64_t code) noexcept : ssi::runtime_error::runtime_error(w, false), _code(code) {
			::syslog(LOG_ERR, " <error> ecat_error(%s, %lld) has been created", w, code);
		}

		/**
		 * get the error code of an exception
		 * @see		ecattyps.h in KPA MDK
		 * @return	negative error code, in case of internal errors
		 *			positive error code which comes from KPA EtherCAT API, on error
		 */
		int64_t code() const { return _code; }

	private:
		int64_t _code;
	};

	/**
	 * defines a type of object to be thrown as a protocol error on communication
	 */
	template<typename T>
	class protocol_error : public ssi::runtime_error
	{
	public:
		protocol_error(const char* const w, const T code) noexcept : ssi::runtime_error::runtime_error(w, false), _code(code) {
			::syslog(LOG_ERR, " <error> protocol_error(%s, %d) has been created", w, code);
		}

		/**
		 * get the error code of an exception
		 * @return	error code
		 */
		T code() const { return _code; }

	private:
		T _code;
	};

	/**
	 * defines a type of object to be thrwon as an runtime exception
	 * it reports the arguments which cannot be accepted by the function
	 */
	class invalid_argument : public ssi::logic_error
	{
	public:
		invalid_argument(const char* what) noexcept : _what(what) { }
		invalid_argument(const std::string& what) noexcept : _what(what) { }
		virtual ~invalid_argument() { }
		virtual const std::string& what() const noexcept { return this->_what; }
	private:
		const std::string _what;
	};

	/**
	 * defines a type of object to be thrown as an runtime exception
	 * it reports that some internal member variable is unacceptable or cannot be supported yet
	 */
	class instance_error : public ssi::logic_error
	{
	public:
		instance_error(const char* what) noexcept : _what(what) { }
		instance_error(const std::string& what) noexcept : _what(what) { }
		virtual ~instance_error() { }
		virtual const std::string& what() const noexcept { return this->_what; }
	private:
		const std::string _what;
	};

	/**
	 * defines a type of object to be thrown as an runtime exception
	 * it reports that some method not implemented is called 
	 */
	class not_implemented : public ssi::logic_error
	{
	public:
		not_implemented(const char* what) noexcept : _what(what) { }
		not_implemented(const std::string& what) noexcept : _what(what) { }
		virtual ~not_implemented() { }
		virtual const std::string& what() const noexcept { return this->_what; }
	private:
		const std::string _what;
	};
}

#endif // __SSI_EXCEPTION_H__
