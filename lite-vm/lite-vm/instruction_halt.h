#ifndef LITE_INSTRUCTION_HALT_H
#define LITE_INSTRUCTION_HALT_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_halt : public instruction
	{
	public:
		instruction_halt();
		virtual ~instruction_halt();

		virtual word bytecode() const;

		virtual std::string regex() const;
		virtual std::vector<word> compile(compiler& pCompiler, const std::vector<std::string>& pArguments) const;

		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif