#include "instruction.h"
#include "instruction_add.h"
#include "virtual_machine.h"

using namespace lite;

virtual_machine::virtual_machine(byte pNumRegisters, word pMemorySize, std::vector<byte>& pProgram)
	:
	mProgramCounter(0),
	mStackPointer(0)
{
	mRegisters = std::vector<word>(pNumRegisters, 0);
	mMemory = std::vector<byte>(pMemorySize, 0);

	if (pProgram.size() > mMemory.size())
		throw std::exception("todo");

	for (word programIt = 0; programIt < pProgram.size(); programIt++)
	{
		mMemory[programIt] = pProgram[programIt];
	}

	register_instruction(std::make_unique<instruction_add>());

	registers(1, 2);
	registers(2, 3);
}
virtual_machine::~virtual_machine()
{
}

void virtual_machine::register_instruction(std::unique_ptr<instruction> pInstruction)
{	
	mInstructions[pInstruction->bytecode()] = std::move(pInstruction);
}

void virtual_machine::step()
{
	byte byte = mMemory[mProgramCounter];

	mInstructions[byte]->execute(*this);
}

word virtual_machine::registers(byte pRegister) const 
{ 
	if (pRegister < mRegisters.size())
		return mRegisters[pRegister];
	else
		return 0;
}
word virtual_machine::program_counter() const
{
	return mProgramCounter;
}
word virtual_machine::stack_pointer() const
{
	return mStackPointer;
}

void virtual_machine::registers(byte pRegister, word pValue) 
{ 
	if(pRegister < mRegisters.size())
		mRegisters[pRegister] = pValue; 
}
//void virtual_machine::byte(word pAddress, byte pValue)
//{
//	if (pAddress < mMemory.size())
//		mMemory[pAddress] = pValue;
//}
void virtual_machine::program_counter(word pProgramCounter) 
{ 
	mProgramCounter = pProgramCounter; 
}
void virtual_machine::stack_pointer(word pStackPointer)
{
	mStackPointer = pStackPointer;
}