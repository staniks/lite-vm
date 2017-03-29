#include "exception.h"
#include "instruction.h"
#include "instruction_add.h"
#include "instruction_load_byte.h"
#include "instruction_set.h"
#include "instruction_store_byte.h"
#include "virtual_machine.h"

using namespace lite;

instruction_set::instruction_set()
{
	register_instruction(std::make_unique<instruction_add>());
	register_instruction(std::make_unique<instruction_load_byte>());
	register_instruction(std::make_unique<instruction_store_byte>());
}
instruction_set::~instruction_set()
{
}

void instruction_set::register_instruction(std::unique_ptr<instruction> pInstruction)
{
	mInstructions[pInstruction->bytecode()] = std::move(pInstruction);
}

void instruction_set::execute(word pInstructionBytecode, virtual_machine& pVirtualMachine)
{
	auto it = mInstructions.find(pInstructionBytecode);
	if (it != mInstructions.end())
		mInstructions[pInstructionBytecode]->execute(pVirtualMachine);
	else
		throw lite::invalid_instruction();
}

std::vector<word> instruction_set::compile(std::string line)
{
	for (auto it = mInstructions.begin(); it != mInstructions.end(); it++)
	{
		auto currentInstruction = it->second.get();
		std::regex regex(currentInstruction->regex(), std::regex_constants::extended);

		std::smatch match;
		if (std::regex_search(line, match, regex))
		{
			std::vector<std::string> arguments;
			for (int i = 1; i < match.size(); i++)
			{
				arguments.push_back(match[i].str());
			}
			return currentInstruction->compile(arguments);
		}
	}
	return std::vector<word>();
}