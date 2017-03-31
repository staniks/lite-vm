#ifndef LITE_INSTRUCTION_JUMP_H
#define LITE_INSTRUCTION_JUMP_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_jump : public instruction
	{
	public:
		instruction_jump();
		virtual ~instruction_jump();

		virtual word bytecode() const;

		virtual std::string regex() const;
		virtual std::vector<word> compile(const compiler& pCompiler, const std::vector<std::string>& pArguments) const;

		virtual void execute(virtual_machine& pVirtualMachine);
	private:
		static const word flag_unconditional = 0x0;
		static const word flag_equal = 0x1;
		static const word flag_not_equal = 0x2;
		static const word flag_greater = 0x3;
		static const word flag_greater_or_equal = 0x4;
		static const word flag_less = 0x5;
		static const word flag_less_or_equal = 0x6;
	};
}

#endif