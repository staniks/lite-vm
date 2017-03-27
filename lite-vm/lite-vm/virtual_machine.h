#ifndef LITE_VIRTUAL_MACHINE_H
#define LITE_VIRTUAL_MACHINE_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

namespace lite
{
	class instruction;

	class virtual_machine
	{
	public:
		virtual_machine(uint8_t pNumRegisters, uint64_t pHeapSize, uint64_t pStackSize);
		~virtual_machine();

		void step();
	private:
		std::vector<uint64_t> mRegisters;
		std::vector<uint64_t> mHeap;
		std::vector<uint64_t> mStack;

		std::map<uint8_t, std::unique_ptr<instruction>> mInstructions;

		uint64_t mProgramCounter;
		uint64_t mStackPointer;
	};
}

#endif