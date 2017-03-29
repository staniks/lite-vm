#ifndef LITE_INSTRUCTION_ADD_H
#define LITE_INSTRUCTION_ADD_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_add : public instruction
	{
	public:
		instruction_add();
		virtual ~instruction_add();

		virtual word bytecode() const;

		virtual std::string regex();
		virtual std::vector<word> compile(std::vector<std::string>& arguments);
		
		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif