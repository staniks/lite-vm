#include <string>

#include "instruction.h"
#include "instruction_add.h"
#include "instruction_factory.h"
#include "virtual_machine.h"

using namespace lite;

instruction_factory::instruction_factory(virtual_machine& pVirtualMachine)
	:
	mVirtualMachine(pVirtualMachine)
{
	mPrototypes[instructions::add] = std::make_unique<instruction_add>(mVirtualMachine);
}
instruction_factory::~instruction_factory()
{
}

std::unique_ptr<instruction> instruction_factory::create(const instructions& pType)
{
	auto it = mPrototypes.find(pType);
	if (it != mPrototypes.end())
		return it->second->clone();
	else
		throw new std::exception("Invalid instruction type specified.");
}