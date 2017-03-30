#ifndef LITE_VIRTUAL_MACHINE_H
#define LITE_VIRTUAL_MACHINE_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "types.h"

namespace lite
{
	class	instruction_set;
	enum class instructions;
	class machine_observer;

	class virtual_machine
	{
	public:
		virtual_machine(const word pNumRegisters, const word pMemorySize, const std::vector<word>& pProgram);
		~virtual_machine();

		bool step();
		void halt();

		void add_observer(machine_observer* observer);

		word program_counter() const;
		word stack_pointer() const;
		word memory(const word pAddress) const;
		std::vector<word> memory_range(const word pAddress, const word pCount) const;
		word registers(const word pRegister) const;

		void program_counter(const word pProgramCounter);
		void stack_pointer(const word pStackPointer);
		void memory(const word pAddress, const word pValue);
		void registers(const word pRegister, const word pValue);

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