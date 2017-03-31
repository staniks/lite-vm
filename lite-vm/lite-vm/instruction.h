#ifndef LITE_INSTRUCTION_H
#define LITE_INSTRUCTION_H

#include <cstdint>
#include <memory>
#include <regex>
#include <vector>

#include "types.h"

namespace lite
{
	class compiler;
	class virtual_machine;

	class instruction
	{
	public:
		instruction();
		virtual ~instruction();

		virtual word bytecode() const = 0;

		virtual std::string regex() const = 0;
		virtual std::vector<word> compile(compiler& pCompiler, const std::vector<std::string>& pArguments) const = 0;
		
		virtual void execute(virtual_machine& pVirtualMachine) = 0;
	};
}

#endif