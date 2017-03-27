#ifndef LITE_VIRTUAL_MACHINE_H
#define LITE_VIRTUAL_MACHINE_H

#include <cstdint>

namespace lite
{
	class virtual_machine
	{
	public:
		virtual_machine(uint8_t pNumRegisters, uint64_t pHeapSize, uint64_t pStackSize);
		~virtual_machine();
	};
}

#endif