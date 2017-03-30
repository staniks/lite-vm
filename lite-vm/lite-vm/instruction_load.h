#ifndef LITE_INSTRUCTION_LOAD_H
#define LITE_INSTRUCTION_LOAD_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_load : public instruction
	{
	public:
		instruction_load();
		virtual ~instruction_load();

		virtual word bytecode() const;

		virtual std::string regex() const;
		virtual std::vector<word> compile(const std::vector<std::string>& pArguments) const;

		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif