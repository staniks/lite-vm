#include "instruction.h"
#include "instruction_factory.h"
#include "virtual_machine.h"

using namespace lite;

virtual_machine::virtual_machine(uint8_t pNumRegisters, uint64_t pHeapSize, uint64_t pStackSize)
	:
	mProgramCounter(0),
	mStackPointer(0)
{
	mRegisters = std::vector<uint64_t>(pNumRegisters, 0);
	mHeap = std::vector<uint64_t>(pHeapSize, 0);
	mStack = std::vector<uint64_t>(pStackSize, 0);

	instruction_factory instructionFactory(*this);

	mInstructions[0] = instructionFactory.create(instructions::add);
}
virtual_machine::~virtual_machine()
{
}

void virtual_machine::step()
{
	mInstructions[0]->execute(std::vector<uint64_t>(2, 1));
}