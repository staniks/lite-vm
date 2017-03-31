#include "compiler.h"
#include "instruction_store.h"
#include "virtual_machine.h"

using namespace lite;

instruction_store::instruction_store() : instruction()
{
}
instruction_store::~instruction_store()
{
}

word instruction_store::bytecode() const
{
	return 0x2;
}

std::string instruction_store::regex() const
{
	return "^str r([0-9]+) ([0-9]+)$";
}

std::vector<word> instruction_store::compile(const compiler& pCompiler, const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(pArguments[0]));
	words.push_back(string_to_word(pArguments[1]));

	return words;
}

void instruction_store::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto register_index = code[1];
	auto address = code[2];

	auto value = pVirtualMachine.registers(register_index);
	pVirtualMachine.memory(address, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}