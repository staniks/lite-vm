#ifndef LITE_INSTRUCTION_FACTORY_H
#define LITE_INSTRUCTION_FACTORY_H

#include <map>
#include <memory>

namespace lite
{
	class instruction;
	class virtual_machine;

	enum class instructions
	{
		add,
	};

	class instruction_factory
	{
	public:
		instruction_factory(virtual_machine& pVirtualMachine);
		~instruction_factory();

		std::unique_ptr<instruction> create(const instructions& pType);
	private:
		virtual_machine& mVirtualMachine;

		std::map<instructions, std::unique_ptr<instruction>> mPrototypes;
	};
}

#endif