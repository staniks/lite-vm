#include <cassert>

#include "exception.h"
#include "instruction.h"
#include "instruction_add.h"
#include "instruction_compare.h"
#include "instruction_halt.h"
#include "instruction_jump.h"
#include "instruction_load.h"
#include "instruction_move.h"
#include "instruction_set.h"
#include "instruction_store.h"
#include "virtual_machine.h"

using namespace lite;

instruction_set::instruction_set()
{
	register_instruction(std::make_unique<instruction_add>());
	register_instruction(std::make_unique<instruction_compare>());
	register_instruction(std::make_unique<instruction_halt>());
	register_instruction(std::make_unique<instruction_jump>());
	register_instruction(std::make_unique<instruction_load>());
	register_instruction(std::make_unique<instruction_move>());
	register_instruction(std::make_unique<instruction_store>());
}
instruction_set::~instruction_set()
{
}

void instruction_set::register_instruction(std::unique_ptr<instruction> pInstruction)
{
	auto it = mInstructions.find(pInstruction->bytecode());
	assert(it == mInstructions.end() && "Instructions cannot have the same bytecode!");

	mInstructions[pInstruction->bytecode()] = std::move(pInstruction);
}

void instruction_set::execute(const word pInstructionBytecode, virtual_machine& pVirtualMachine)
{
	auto it = mInstructions.find(pInstructionBytecode);
	if (it != mInstructions.end())
		mInstructions[pInstructionBytecode]->execute(pVirtualMachine);
	else
		throw lite::invalid_instruction_exception(pVirtualMachine.program_counter());
}

std::vector<word> instruction_set::compile(const std::string& pLine) const
{
	for (auto it = mInstructions.begin(); it != mInstructions.end(); it++)
	{
		auto currentInstruction = it->second.get();
		std::regex regex(currentInstruction->regex(), std::regex_constants::extended);

		std::smatch match;
		if (std::regex_search(pLine, match, regex))
		{
			std::vector<std::string> arguments;
			for (size_t i = 1; i < match.size(); i++)
			{
				arguments.push_back(match[i].str());
			}
			return currentInstruction->compile(arguments);
		}
	}
	return std::vector<word>();
}