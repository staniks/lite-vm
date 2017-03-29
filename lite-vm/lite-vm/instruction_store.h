#ifndef LITE_INSTRUCTION_STORE_H
#define LITE_INSTRUCTION_STORE_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_store : public instruction
	{
	public:
		instruction_store();
		virtual ~instruction_store();

		virtual word bytecode() const;

		virtual std::string regex();
		virtual std::vector<word> compile(std::vector<std::string>& pArguments);

		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif