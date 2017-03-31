#include "compiler.h"
#include "instruction_load.h"
#include "virtual_machine.h"

using namespace lite;

instruction_load::instruction_load() : instruction()
{
}
instruction_load::~instruction_load()
{
}

word instruction_load::bytecode() const
{
	return 0x3;
}

std::string instruction_load::regex() const
{
	return "^ldr ([0-9]+) r([0-9]+)$";
}

std::vector<word> instruction_load::compile(const compiler& pCompiler, const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(pArguments[0]));
	words.push_back(string_to_word(pArguments[1]));

	return words;
}

void instruction_load::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto address = code[1];
	auto register_index = code[2];

	auto value = pVirtualMachine.memory(address);
	pVirtualMachine.registers(register_index, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}