#ifndef LITE_VIRTUAL_MACHINE_H
#define LITE_VIRTUAL_MACHINE_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "types.h"

namespace lite
{
	class instruction;
	enum class instructions;

	class virtual_machine
	{
	public:
		virtual_machine(byte pNumRegisters, word pMemorySize, std::vector<byte>& pProgram);
		~virtual_machine();

		void register_instruction(std::unique_ptr<instruction> pInstruction);

		void step();

		word registers(byte pRegister) const;
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
				return 0;
		}

		void registers(byte pRegister, word pValue);
		void program_counter(word pProgramCounter);
		void stack_pointer(word pStackPointer);

		template <typename T>
		void memory(word pAddress, T pValue) const
		{
			if (pAddress + sizeof(T) - 1 < mMemory.size())
			{
				T* value = (T*)&mMemory[pAddress];
				*value = pValue;
			}
		}

	private:
		std::vector<word> mRegisters;
		std::vector<byte> mMemory;

		std::map<byte, std::unique_ptr<instruction>> mInstructions;

		word mProgramCounter;
		word mStackPointer;
	};
}

#endif