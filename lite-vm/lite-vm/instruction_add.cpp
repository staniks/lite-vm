#include <iostream> //deleteme

#include "instruction_add.h"
#include "virtual_machine.h"

using namespace lite;

instruction_add::instruction_add(virtual_machine& pVirtualMachine) : instruction(pVirtualMachine)
{
}
instruction_add::~instruction_add()
{
}

std::unique_ptr<instruction> instruction_add::clone()
{
	return std::make_unique<instruction_add>(mVirtualMachine);
}
void instruction_add::execute(std::vector<uint64_t>& pArguments)
{
	std::cout << pArguments[0] + pArguments[1] << std::endl;
}