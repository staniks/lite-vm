#ifndef LITE_TYPES_H
#define LITE_TYPES_H

#include <cstdint>
#include <string>

namespace lite
{
	typedef uint32_t word;
	typedef int32_t signed_word;

	word string_to_word(const std::string& pString);
}

#endif