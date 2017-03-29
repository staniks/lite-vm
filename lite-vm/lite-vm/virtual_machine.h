#ifndef LITE_VIRTUAL_MACHINE_H
#define LITE_VIRTUAL_MACHINE_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "exception.h"
#include "types.h"

namespace lite
{
	class instruction_set;
	enum class instructions;

	class virtual_machine
	{
	public:
		virtual_machine(byte pNumRegisters, word pMemorySize, std::vector<byte>& pProgram);
		~virtual_machine();

		void step();

		word program_counter() const;
		word stack_pointer() const;

		template <typename T>
		T memory(word pAddress) const
		{
			if (pAddress + sizeof(T) - 1 < mMemory.size())
			{
				T* value = (T*)&mMemory[pAddress];
				return *value;
			}
			else
				throw lite::out_of_bounds_exception();
		}

		template <typename T>
		T registers(byte pRegister) const
		{
			if (pRegister < mRegisters.size())
				return (T)mRegisters[pRegister];
			else
				throw lite::out_of_bounds_exception();
		}

		void program_counter(word pProgramCounter);
		void stack_pointer(word pStackPointer);

		template <typename T>
		void memory(word pAddress, T pValue)
		{
			if (pAddress + sizeof(T) - 1 < mMemory.size())
			{
				T* value = (T*)&mMemory[pAddress];
				*value = pValue;
			}
			else
				throw lite::out_of_bounds_exception();
		}

		template <typename T>
		void registers(byte pRegister, T pValue)
		{
			if (pRegister < mRegisters.size())
				mRegisters[pRegister] = (T)pValue;
			else
				throw lite::out_of_bounds_exception();
		}

	private:
		std::vector<word> mRegisters;
		std::vector<byte> mMemory;

		std::unique_ptr<instruction_set> mInstructionSet;

		word mProgramCounter;
		word mStackPointer;
	};
}

#endif