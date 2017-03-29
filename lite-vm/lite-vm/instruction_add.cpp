#include <iostream> //deleteme

#include "instruction_add.h"
#include "virtual_machine.h"

using namespace lite;

instruction_add::instruction_add() : instruction()
{
}
instruction_add::~instruction_add()
{
}

byte instruction_add::bytecode() const
{
	return 0x1;
}

std::string instruction_add::regex()
{
	return "^add (r[0-9]+) (r[0-9]+) (r[0-9]+)$";
}

std::vector<byte> instruction_add::compile(std::smatch match)
{
	return std::vector<byte>();
}

void instruction_add::execute(virtual_machine& pVirtualMachine)
{
	auto arg1 = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + 1);
	auto arg2 = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + 2);
	auto arg3 = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + 3);

	auto value1 = pVirtualMachine.registers<word>(arg1);
	auto value2 = pVirtualMachine.registers<word>(arg2);
	auto result = value1 + value2;

	pVirtualMachine.registers<word>(arg3, result);

	std::cout << result << std::endl;

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + 4);
}