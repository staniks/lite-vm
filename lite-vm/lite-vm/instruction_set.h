#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <map>
#include <memory>
#include <vector>

#include "types.h"

namespace lite
{
	class instruction;
	class virtual_machine;

	class instruction_set
	{
	public:
		instruction_set();
		~instruction_set();

		void register_instruction(std::unique_ptr<instruction> pInstruction);

		void execute(byte pInstructionBytecode, virtual_machine& pVirtualMachine);

		std::vector<byte> compile(std::string line);
	private:
		std::map<byte, std::unique_ptr<instruction>> mInstructions;
	};
}

#endif