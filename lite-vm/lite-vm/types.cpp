#include <regex>

#include "types.h"

using namespace lite;

word lite::string_to_word(const std::string& pString)
{
	return std::atoi(pString.c_str());
}
std::string lite::trim(const std::string& pString)
{
	std::string trimmed = std::regex_replace(pString, std::regex("^\\s+"), "");
	return std::regex_replace(trimmed, std::regex("\\s+$"), "");
}