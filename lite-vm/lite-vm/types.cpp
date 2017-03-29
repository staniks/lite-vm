#include "types.h"

using namespace lite;

word lite::string_to_word(std::string& str)
{
	return std::atoi(str.c_str());
}