#include <iostream>
#include <virtual_machine.h>
#include <regex>

#include <compiler.h>

int main()
{
	std::stringstream str;
	str << "ldb 32 r1" << std::endl;
	str << "stb r1 33" << std::endl;

	std::vector<lite::byte> bytes = lite::compiler::compile(str);

	std::vector<lite::byte> program = 
	{ 
		0x3, 32, 0, 0, 0, 1,
		0x2, 1, 33, 0, 0, 0
	};
	lite::virtual_machine virtualMachine(8, 1000, program);

	virtualMachine.memory<lite::byte>(32, 9);

	while (true)
	{
		try
		{
			virtualMachine.step();
		}
		catch (lite::out_of_bounds_exception const& e)
		{						
			std::cout << e.what() << std::endl;
			break;
		}
		catch (lite::invalid_instruction const& e)
		{
			std::cout << e.what() << std::endl;
			break;
		}
	}	

	std::cout << virtualMachine.registers<lite::word>(1) << std::endl;
	std::cout << virtualMachine.memory<lite::word>(33) << std::endl;

	return 0;
}