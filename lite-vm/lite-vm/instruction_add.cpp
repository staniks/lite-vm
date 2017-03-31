#include "compiler.h"
#include "instruction_add.h"
#include "virtual_machine.h"

using namespace lite;

instruction_add::instruction_add() : instruction()
{
}
instruction_add::~instruction_add()
{
}

word instruction_add::bytecode() const
{
	return 0x1;
}

std::string instruction_add::regex() const
{
	return "^add r([0-9]+) r([0-9]+) r([0-9]+)$";
}

std::vector<word> instruction_add::compile(compiler& pCompiler, const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(pArguments[0]));
	words.push_back(string_to_word(pArguments[1]));
	words.push_back(string_to_word(pArguments[2]));

	return words;
}

void instruction_add::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 4);

	auto register_index_1 = code[1];
	auto register_index_2 = code[2];
	auto register_index_3 = code[3];

	auto value1 = pVirtualMachine.registers(register_index_1);
	auto value2 = pVirtualMachine.registers(register_index_2);
	auto result = value1 + value2;

	pVirtualMachine.registers(register_index_3, result);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}