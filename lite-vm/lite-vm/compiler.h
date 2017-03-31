#ifndef LITE_COMPILER_H
#define LITE_COMPILER_H

#include <istream>
#include <map>
#include <vector>

#include "types.h"

namespace lite
{
	class compiler
	{
	public:
		std::vector<word> compile(std::istream& pStream);

		word label(const std::string pLabel) const;
	private:
		size_t mCurrentLine;

		std::map<std::string, word> mLabels;
	};
}

#endif