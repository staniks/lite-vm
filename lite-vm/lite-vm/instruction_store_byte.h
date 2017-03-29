#ifndef LITE_INSTRUCTION_STORE_BYTE_H
#define LITE_INSTRUCTION_STORE_BYTE_H

#include "instruction.h"
#include "types.h"

namespace lite
{
	class instruction_store_byte : public instruction
	{
	public:
		instruction_store_byte();
		virtual ~instruction_store_byte();

		virtual word bytecode() const;

		virtual std::string regex();
		virtual std::vector<word> compile(std::vector<std::string>& arguments);

		virtual void execute(virtual_machine& pVirtualMachine);
	};
}

#endif