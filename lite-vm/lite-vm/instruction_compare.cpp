#include "instruction_compare.h"
#include "virtual_machine.h"

using namespace lite;

instruction_compare::instruction_compare() : instruction()
{
}
instruction_compare::~instruction_compare()
{
}

word instruction_compare::bytecode() const
{
	return 0x5;
}

std::string instruction_compare::regex() const
{
	return "^cmp r([0-9]+) r([0-9]+)$";
}

std::vector<word> instruction_compare::compile(const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(pArguments[0]));
	words.push_back(string_to_word(pArguments[1]));

	return words;
}

void instruction_compare::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto registerIndex1 = code[1];
	auto registerIndex2 = code[2];

	lite::signed_word value1 = (lite::signed_word)pVirtualMachine.registers(registerIndex1);
	lite::signed_word value2 = (lite::signed_word)pVirtualMachine.registers(registerIndex2);

	pVirtualMachine.compare_flag(value1 - value2);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}