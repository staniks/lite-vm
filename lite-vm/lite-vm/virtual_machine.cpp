#include "instruction_set.h"
#include "virtual_machine.h"

using namespace lite;

virtual_machine::virtual_machine(byte pNumRegisters, word pMemorySize, std::vector<byte>& pProgram)
	:
	mProgramCounter(0),
	mStackPointer(0)
{
	mRegisters = std::vector<word>(pNumRegisters, 0);
	mMemory = std::vector<byte>(pMemorySize, 0);

	for (word programIt = 0; programIt < pProgram.size(); programIt++)
	{
		memory<byte>(programIt, pProgram[programIt]);
	}

	mInstructionSet = std::make_unique<instruction_set>();
}
virtual_machine::~virtual_machine()
{
}

void virtual_machine::step()
{
	byte instructionBytecode = memory<byte>(mProgramCounter);

	mInstructionSet->execute(instructionBytecode, *this);
}

word virtual_machine::program_counter() const
{
	return mProgramCounter;
}
word virtual_machine::stack_pointer() const
{
	return mStackPointer;
}

void virtual_machine::program_counter(word pProgramCounter) 
{ 
	mProgramCounter = pProgramCounter; 
}
void virtual_machine::stack_pointer(word pStackPointer)
{
	mStackPointer = pStackPointer;
}