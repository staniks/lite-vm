#ifndef LITE_EXCEPTION_H
#define LITE_EXCEPTION_H

#include <exception>

#include "types.h"

namespace lite
{
	class exception : public std::exception
	{
	public:
		exception();
		virtual ~exception();
	};

	class runtime_exception : public lite::exception
	{
	public:
		runtime_exception(const word pProgramCounter);
		virtual ~runtime_exception();

		word where() const;
	protected:
		word mProgramCounter;
	};

	class invalid_address_exception : public lite::runtime_exception
	{
	public:
		invalid_address_exception(const word pProgramCounter, const word pAddress);
		virtual ~invalid_address_exception();

		inline word address() const { return mAddress; }
		virtual char const * what() const;
	private:
		word mAddress;
	};

	class invalid_register_exception : public lite::runtime_exception
	{
	public:
		invalid_register_exception(const word pProgramCounter, const word pRegister);
		virtual ~invalid_register_exception();

		inline word register_index() const { return mRegister; }
		virtual char const * what() const;
	private:
		word mRegister;
	};

	class invalid_instruction_exception : public lite::runtime_exception
	{
	public:
		invalid_instruction_exception(const word pProgramCounter);
		virtual ~invalid_instruction_exception();
		virtual char const * what() const;
	};

	class compiler_exception : lite::exception
	{
	public:
		compiler_exception(const size_t pLine, const std::string pMessage);
		virtual char const * what() const;

		size_t line() const;
	private:
		std::string mMessage;
		size_t mLine;
	};
}

#endif