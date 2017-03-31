#include "compiler.h"
#include "instruction_move.h"
#include "virtual_machine.h"

using namespace lite;

instruction_move::instruction_move() : instruction()
{
}
instruction_move::~instruction_move()
{
}

word instruction_move::bytecode() const
{
	return 0x4;
}

std::string instruction_move::regex() const
{
	return "^mov ([0-9]+) r([0-9]+)$";
}

std::vector<word> instruction_move::compile(compiler& pCompiler, const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(pArguments[0]));
	words.push_back(string_to_word(pArguments[1]));

	return words;
}

void instruction_move::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto value = code[1];
	auto register_index = code[2];

	pVirtualMachine.registers(register_index, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}