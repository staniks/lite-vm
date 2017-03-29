#ifndef LITE_EXCEPTION_H
#define LITE_EXCEPTION_H

#include <exception>

namespace lite
{
	class exception : public std::exception
	{
	};

	class out_of_bounds_exception : public lite::exception
	{
	public:
		virtual char const * what() const { return "Address out of bounds."; }
	};

	class invalid_instruction : public lite::exception
	{
	public:
		virtual char const * what() const { return "Invalid instruction code."; }
	};
}

#endif