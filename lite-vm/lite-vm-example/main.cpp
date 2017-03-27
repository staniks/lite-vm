#include <virtual_machine.h>

int main()
{
	lite::virtual_machine virtualMachine(8, 128, 64);
	virtualMachine.step();
	return 0;
}