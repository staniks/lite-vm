#include <iostream>
#include <virtual_machine.h>
#include <regex>

#include <compiler.h>
#include <sstream>

int main()
{
	std::stringstream str;
	str << "ldb 32 r1" << std::endl;
	str << "add r1 r1 r2" << std::endl;
	str << "stb r2 33" << std::endl;

	std::vector<lite::word> program = lite::compiler::compile(str);

	lite::virtual_machine virtualMachine(8, 1024, program);

	virtualMachine.memory(32, 9);

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

	std::cout << virtualMachine.registers(1) << std::endl;
	std::cout << virtualMachine.memory(33) << std::endl;

	return 0;
}