#ifndef LITE_INSTRUCTION_MOVE_H
#define LITE_INSTRUCTION_MOVE_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_move : public instruction
	{
	public:
		instruction_move();
		virtual ~instruction_move();

		virtual word bytecode() const;

		virtual std::string regex() const;
		virtual std::vector<word> compile(compiler& pCompiler, const std::vector<std::string>& pArguments) const;

		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif