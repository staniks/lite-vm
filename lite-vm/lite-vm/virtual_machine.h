#ifndef LITE_VIRTUAL_MACHINE_H
#define LITE_VIRTUAL_MACHINE_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "types.h"

namespace lite
{
	class instruction_set;
	enum class instructions;
	class machine_observer;

	class virtual_machine
	{
	public:
		virtual_machine(word pNumRegisters, word pMemorySize, std::vector<word>& pProgram);
		~virtual_machine();

		bool step();
		void halt();

		void add_observer(machine_observer* observer);

		word program_counter() const;
		word stack_pointer() const;
		word memory(word pAddress) const;
		std::vector<word> memory_range(word pAddress, word pCount) const;
		word registers(word pRegister) const;

		void program_counter(word pProgramCounter);
		void stack_pointer(word pStackPointer);
		void memory(word pAddress, word pValue);
		void registers(word pRegister, word pValue);

	private:
		std::vector<word> mRegisters;
		std::vector<word> mMemory;

		std::unique_ptr<instruction_set> mInstructionSet;

		std::vector<machine_observer*> mObservers;

		word mProgramCounter;
		word mStackPointer;

		bool mHalted;
	};
}

#endif