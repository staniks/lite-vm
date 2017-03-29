#include "instruction_load_byte.h"
#include "virtual_machine.h"

using namespace lite;

instruction_load_byte::instruction_load_byte() : instruction()
{
}
instruction_load_byte::~instruction_load_byte()
{
}

word instruction_load_byte::bytecode() const
{
	return 0x3;
}

std::string instruction_load_byte::regex()
{
	return "^ldb ([0-9]+) r([0-9]+)$";
}

std::vector<word> instruction_load_byte::compile(std::vector<std::string>& arguments)
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(arguments[0]));
	words.push_back(string_to_word(arguments[1]));

	return words;
}

void instruction_load_byte::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto address = code[1];
	auto register_index = code[2];

	auto value = pVirtualMachine.memory(address);
	pVirtualMachine.registers(register_index, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}