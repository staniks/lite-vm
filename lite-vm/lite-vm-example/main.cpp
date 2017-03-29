#include <iostream>
#include <sstream>
#include <lite_vm.h>

class example_observer : public lite::machine_observer
{
public:
	virtual void on_register_write(lite::word pRegister, lite::word pValue)
	{
		std::cout << "Written " << pValue << " into register " << "[R" << pRegister << "]." << std::endl;
	}
	virtual void on_memory_write(lite::word pAddress, lite::word pValue)
	{
		std::cout << "Written " << pValue << " on memory address " << "[" << pAddress << "]." << std::endl;
	}
};

int main(int argc, char** argv)
{
	std::stringstream exampleSourceStream;

	exampleSourceStream << "ldb 32 r1" << std::endl;
	exampleSourceStream << "add r1 r1 r2" << std::endl;
	exampleSourceStream << "stb r2 33" << std::endl;

	std::vector<lite::word> exampleProgram = lite::compiler::compile(exampleSourceStream);

	lite::virtual_machine virtualMachine(8, 1024, exampleProgram);

	example_observer o;
	virtualMachine.add_observer(&o);

	virtualMachine.memory(32, 9);

	try
	{
		while (virtualMachine.step());
	}	
	catch (lite::out_of_bounds_exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (lite::invalid_instruction const& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}