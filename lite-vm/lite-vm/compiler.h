#ifndef LITE_COMPILER_H
#define LITE_COMPILER_H

#include <istream>
#include <vector>

#include "types.h"

namespace lite
{
	class compiler
	{
	public:
		static std::vector<word> compile(std::istream& stream);
	};
}

#endif