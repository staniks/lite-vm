#ifndef LITE_COMPILER_H
#define LITE_COMPILER_H

#include <sstream>
#include <vector>

#include "types.h"

namespace lite
{
	class compiler
	{
	public:
		static std::vector<byte> compile(std::stringstream& stream);
	};
}

#endif