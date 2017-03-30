#ifndef LITE_INSTRUCTION_COMPARE_H
#define LITE_INSTRUCTION_COMPARE_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_compare : public instruction
	{
	public:
		instruction_compare();
		virtual ~instruction_compare();

		virtual word bytecode() const;

		virtual std::string regex() const;
		virtual std::vector<word> compile(const std::vector<std::string>& pArguments) const;

		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif