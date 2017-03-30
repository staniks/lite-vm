#ifndef LITE_EXCEPTION_H
#define LITE_EXCEPTION_H

#include <exception>

#include "types.h"

namespace lite
{
	class exception : public std::exception
	{
	public:
		exception(word pProgramCounter);
		virtual ~exception();

		word where() const;
	protected:
		word mProgramCounter;
	};

	class invalid_address_exception : public lite::exception
	{
	public:
		invalid_address_exception(word pProgramCounter, word pAddress);
		virtual ~invalid_address_exception();

		inline word address() const { return mAddress; }
		virtual char const * what() const;
	private:
		word mAddress;
	};

	class invalid_register_exception : public lite::exception
	{
	public:
		invalid_register_exception(word pProgramCounter, word pRegister);
		virtual ~invalid_register_exception();

		inline word register_index() const { return mRegister; }
		virtual char const * what() const;
	private:
		word mRegister;
	};

	class invalid_instruction_exception : public lite::exception
	{
	public:
		invalid_instruction_exception(word pProgramCounter);
		virtual ~invalid_instruction_exception();
		virtual char const * what() const;
	};
}

#endif