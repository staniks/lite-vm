#include "instruction_load_byte.h"
#include "virtual_machine.h"

using namespace lite;

instruction_load_byte::instruction_load_byte() : instruction()
{
}
instruction_load_byte::~instruction_load_byte()
{
}

byte instruction_load_byte::bytecode() const
{
	return 0x3;
}

std::string instruction_load_byte::regex()
{
	return "^ldb ([0-9]+) (r[0-9]+)$";
}

std::vector<byte> instruction_load_byte::compile(std::smatch match)
{
	auto code = bytecode();
	word arg1 = atoi(match[1].str().c_str());
	byte arg2 = atoi(match[2].str().c_str());

	word instruction_size = sizeof(code) + sizeof(arg1) + sizeof(arg2);

	std::vector<byte> bytes = std::vector<byte>(instruction_size, 0);

	*(&bytes[0]) = code;
	*(&bytes[sizeof(code)]) = arg1 << 8;

	return bytes;
}

void instruction_load_byte::execute(virtual_machine& pVirtualMachine)
{
	auto code = bytecode();
	word programCounterDelta = sizeof(code);

	auto address = pVirtualMachine.memory<word>(pVirtualMachine.program_counter() + programCounterDelta);  
	programCounterDelta += sizeof(address);

	auto reg = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + programCounterDelta);  
	programCounterDelta += sizeof(reg);

	auto value = pVirtualMachine.memory<byte>(address);

	pVirtualMachine.registers<byte>(reg, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + programCounterDelta);
}