#include <virtual_machine.h>

int main()
{
	std::vector<lite::byte> program = { 0x01, 1, 2, 3 };
	lite::virtual_machine virtualMachine(8, 128, program);

	virtualMachine.step();
	return 0;
}