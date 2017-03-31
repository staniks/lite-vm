#include "instruction_jump.h"
#include "virtual_machine.h"

using namespace lite;

instruction_jump::instruction_jump() : instruction()
{
}
instruction_jump::~instruction_jump()
{
}

word instruction_jump::bytecode() const
{
	return 0x6;
}

std::string instruction_jump::regex() const
{
	return "^jmp ([0-9]+) (uc|eq|ne|gt|ge|ls|le)$";
}

std::vector<word> instruction_jump::compile(const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());
	words.push_back(string_to_word(pArguments[0]));

	auto conditionArgument = pArguments[1];
	word condition = flag_unconditional;

	if (conditionArgument == "eq") condition = flag_equal;
	if (conditionArgument == "ne") condition = flag_not_equal;
	if (conditionArgument == "gt") condition = flag_greater;
	if (conditionArgument == "ge") condition = flag_greater_or_equal;
	if (conditionArgument == "ls") condition = flag_less;
	if (conditionArgument == "le") condition = flag_less_or_equal;

	words.push_back(condition);

	return words;
}

void instruction_jump::execute(virtual_machine& pVirtualMachine)
{
	auto code = pVirtualMachine.memory_range(pVirtualMachine.program_counter(), 3);

	auto address = code[1];
	auto condition = code[2];
	bool jump = false;

	lite::signed_word compareFlag = pVirtualMachine.compare_flag();

	switch (condition)
	{
	case flag_unconditional: jump = true; break;
	case flag_equal: if (compareFlag == 0) jump = true; break;
	case flag_not_equal: if (compareFlag != 0) jump = true; break;
	case flag_greater: if (compareFlag > 0) jump = true; break;
	case flag_greater_or_equal: if (compareFlag >= 0) jump = true; break;
	case flag_less: if (compareFlag < 0) jump = true; break;
	case flag_less_or_equal: if (compareFlag <= 0) jump = true; break;
	default: jump = false; break;
	}

	if(jump)
		pVirtualMachine.program_counter(address);
	else
		pVirtualMachine.program_counter(pVirtualMachine.program_counter() + (word)code.size());
}