#ifndef LITE_TYPES_H
#define LITE_TYPES_H

#include <cstdint>
#include <string>

namespace lite
{
	typedef uint32_t word;

	word string_to_word(std::string& pString);
}

#endif