#include "compilation_process.h"
#include "instruction_halt.h"
#include "virtual_machine.h"

using namespace lite;

instruction_halt::instruction_halt() : instruction()
{
}
instruction_halt::~instruction_halt()
{
}

word instruction_halt::bytecode() const
{
	return 0x0;
}

std::string instruction_halt::regex() const
{
	return "^halt$";
}

std::vector<word> instruction_halt::compile(compilation_process& pCompilationProcess, const std::vector<std::string>& pArguments) const
{
	auto words = std::vector<word>();

	words.push_back(bytecode());

	return words;
}

void instruction_halt::execute(virtual_machine& pVirtualMachine)
{
	pVirtualMachine.halt();
}