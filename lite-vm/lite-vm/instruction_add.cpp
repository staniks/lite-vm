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
	return 0x01;
}

void instruction_add::execute(virtual_machine& pVirtualMachine)
{
	byte arg1 = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + 1);
	byte arg2 = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + 2);
	byte arg3 = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + 3);

	word value1 = pVirtualMachine.registers(arg1);
	word value2 = pVirtualMachine.registers(arg2);
	word result = value1 + value2;

	pVirtualMachine.registers(arg3, result);

	std::cout << result << std::endl;

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + 4);
}