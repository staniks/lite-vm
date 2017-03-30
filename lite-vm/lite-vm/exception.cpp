#include <sstream>

#include "exception.h"

using namespace lite;

exception::exception() {}
exception::~exception() {}

runtime_exception::runtime_exception(const word pProgramCounter) : mProgramCounter(pProgramCounter) {}
runtime_exception::~runtime_exception() {}
word runtime_exception::where() const
{
	return mProgramCounter;
}

invalid_address_exception::invalid_address_exception(const word pProgramCounter, const word pAddress) : runtime_exception(pProgramCounter), mAddress(pAddress) {}
invalid_address_exception::~invalid_address_exception() {}
char const * invalid_address_exception::what() const 
{ 
	return "Address out of bounds.";
}

invalid_register_exception::invalid_register_exception(const word pProgramCounter, const word pRegister) : runtime_exception(pProgramCounter), mRegister(pRegister) {}
invalid_register_exception::~invalid_register_exception() {}
char const * invalid_register_exception::what() const
{
	return "Register out of bounds.";
}

invalid_instruction_exception::invalid_instruction_exception(const word pProgramCounter) : runtime_exception(pProgramCounter) {}
invalid_instruction_exception::~invalid_instruction_exception() {}
char const * invalid_instruction_exception::what() const
{
	return "Invalid instruction code.";
}

compiler_exception::compiler_exception(const size_t pLine) : mLine(pLine) {}
char const * compiler_exception::what() const
{
	return "Compile error.";
}
size_t compiler_exception::line() const
{
	return mLine;
}