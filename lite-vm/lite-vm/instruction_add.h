#ifndef LITE_INSTRUCTION_ADD_H
#define LITE_INSTRUCTION_ADD_H

#include "instruction.h"

namespace lite
{
	class instruction_add : public instruction
	{
	public:
		instruction_add(virtual_machine& pVirtualMachine);
		virtual ~instruction_add();

		virtual std::unique_ptr<instruction> clone();
		virtual void execute(std::vector<uint64_t>& pArguments);
	};
}

#endif