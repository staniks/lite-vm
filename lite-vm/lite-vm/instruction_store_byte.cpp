#include "instruction_store_byte.h"
#include "virtual_machine.h"

using namespace lite;

instruction_store_byte::instruction_store_byte() : instruction()
{
}
instruction_store_byte::~instruction_store_byte()
{
}

byte instruction_store_byte::bytecode() const
{
	return 0x2;
}

std::string instruction_store_byte::regex()
{
	return "^stb (r[0-9]+) ([0-9]+)$";
}

std::vector<byte> instruction_store_byte::compile(std::smatch match)
{
	return std::vector<byte>();
}

void instruction_store_byte::execute(virtual_machine& pVirtualMachine)
{
	auto byteCode = bytecode();
	word programCounterDelta = sizeof(byteCode);

	auto reg = pVirtualMachine.memory<byte>(pVirtualMachine.program_counter() + programCounterDelta); 
	programCounterDelta += sizeof(reg);

	auto address = pVirtualMachine.memory<word>(pVirtualMachine.program_counter() + programCounterDelta);
	programCounterDelta += sizeof(address);

	auto value = pVirtualMachine.registers<byte>(reg);

	pVirtualMachine.memory<byte>(address, value);

	pVirtualMachine.program_counter(pVirtualMachine.program_counter() + programCounterDelta);
}