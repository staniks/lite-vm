#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <map>
#include <memory>
#include <vector>

#include "types.h"

namespace lite
{
	class compiler;
	class instruction;
	class virtual_machine;

	class instruction_set
	{
	public:
		instruction_set();
		~instruction_set();

		void register_instruction(std::unique_ptr<instruction> pInstruction);

		void execute(const word pInstructionBytecode, virtual_machine& pVirtualMachine);

		std::vector<word> compile(const compiler& pCompiler, const std::string& pLine) const;
	private:
		std::map<word, std::unique_ptr<instruction>> mInstructions;
	};
}

#endif