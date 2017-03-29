#include "exception.h"
#include "instruction_set.h"
#include "machine_observer.h"
#include "virtual_machine.h"

using namespace lite;

virtual_machine::virtual_machine(word pNumRegisters, word pMemorySize, std::vector<word>& pProgram)
	:
	mProgramCounter(0),
	mStackPointer(0),
	mHalted(false)
{
	mRegisters = std::vector<word>(pNumRegisters, 0);
	mMemory = std::vector<word>(pMemorySize, 0);

	for (word programIt = 0; programIt < pProgram.size(); programIt++)
	{
		memory(programIt, pProgram[programIt]);
	}

	mInstructionSet = std::make_unique<instruction_set>();
}
virtual_machine::~virtual_machine()
{
}

void virtual_machine::add_observer(machine_observer* observer)
{
	mObservers.push_back(observer);
}

bool virtual_machine::step()
{
	if (mHalted)
		return !mHalted;

	mInstructionSet->execute(memory(mProgramCounter), *this);

	return !mHalted;
}

void virtual_machine::halt()
{
	mHalted = true;
}

word virtual_machine::program_counter() const
{
	return mProgramCounter;
}
word virtual_machine::stack_pointer() const
{
	return mStackPointer;
}
word virtual_machine::memory(word pAddress) const
{
	if (pAddress < mMemory.size())
	{
		return mMemory[pAddress];
	}
	else
		throw lite::out_of_bounds_exception();
}
std::vector<word> virtual_machine::memory_range(word pAddress, word pCount) const
{
	std::vector<word> range;
	for (word i = 0; i < pCount; i++)
		range.push_back(memory(pAddress + i));
	return range;
}
word virtual_machine::registers(word pRegister) const
{
	if (pRegister < mRegisters.size())
		return mRegisters[pRegister];
	else
		throw lite::out_of_bounds_exception();
}

void virtual_machine::program_counter(word pProgramCounter) 
{ 
	mProgramCounter = pProgramCounter; 
}
void virtual_machine::stack_pointer(word pStackPointer)
{
	mStackPointer = pStackPointer;
}
void virtual_machine::memory(word pAddress, word pValue)
{
	if (pAddress < mMemory.size())
	{
		mMemory[pAddress] = pValue;
		for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		{
			(*it)->on_memory_write(pAddress, pValue);
		}
	}
	else
		throw lite::out_of_bounds_exception();
}
void virtual_machine::registers(word pRegister, word pValue)
{
	if (pRegister < mRegisters.size())
	{
		mRegisters[pRegister] = pValue;
		for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		{
			(*it)->on_register_write(pRegister, pValue);
		}
	}
	else
		throw lite::out_of_bounds_exception();
}