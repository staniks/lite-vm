#ifndef LITE_INSTRUCTION_H
#define LITE_INSTRUCTION_H

#include <cstdint>
#include <memory>
#include <vector>

namespace lite
{
	class virtual_machine;

	class instruction
	{
	public:
		instruction(virtual_machine& pVirtualMachine);
		virtual ~instruction();

		virtual std::unique_ptr<instruction> clone() = 0;
		virtual void execute(std::vector<uint64_t>& pArguments) = 0;

	protected:
		virtual_machine& mVirtualMachine;
	};
}

#endif