#include "instruction.h"
#include "virtual_machine.h"

using namespace lite;

instruction::instruction(virtual_machine& pVirtualMachine)
	:
	mVirtualMachine(pVirtualMachine)
{
}

instruction::~instruction()
{
}