#include "instruction_store_byte.h"
#include "virtual_machine.h"

using namespace lite;

instruction_store_byte::instruction_store_byte() : instruction()
{
}
instruction_store_byte::~instruction_store_byte()
{
}

word instruction_store_byte::bytecode() const
{
	return 0x2;
}

std::string instruction_store_byte::regex()
{
	return "^stb r([0-9]+) ([0-9]+)$";
}

std::vector<word> instruction_store_byte::compile(std::vector<std::string>& arguments)
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(arguments[0]));
	words.push_back(string_to_word(arguments[1]));

	return words;
}

void instruction_store_byte::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto register_index = code[1];
	auto address = code[2];

	auto value = pVirtualMachine.registers(register_index);
	pVirtualMachine.memory(address, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}