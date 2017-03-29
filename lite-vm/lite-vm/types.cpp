#include "types.h"

using namespace lite;

word lite::string_to_word(std::string& pString)
{
	return std::atoi(pString.c_str());
}