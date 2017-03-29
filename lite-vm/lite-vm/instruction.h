#ifndef LITE_INSTRUCTION_H
#define LITE_INSTRUCTION_H

#include <cstdint>
#include <memory>
#include <regex>
#include <vector>

#include "types.h"

namespace lite
{
	class virtual_machine;

	class instruction
	{
	public:
		instruction();
		virtual ~instruction();

		virtual byte bytecode() const = 0;

		virtual std::string regex() = 0;
		virtual std::vector<byte> compile(std::smatch match) = 0;
		
		virtual void execute(virtual_machine& pVirtualMachine) = 0;
	};
}

#endif