#include <iostream>
#include <fstream>
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
	std::ifstream exampleSourceStream("example_program.ass");

	std::vector<lite::word> exampleProgram = lite::compiler::compile(exampleSourceStream);

	lite::virtual_machine virtualMachine(8, 64, exampleProgram);

	example_observer o;
	virtualMachine.add_observer(&o);

	virtualMachine.memory(32, 9);

	try
	{
		while (virtualMachine.step());
	}	
	catch (lite::invalid_address_exception const& e)
	{
		std::cout << e.what() << " [Address: " << e.address() << ",  PC: " << e.where() << "]." << std::endl;
	}
	catch (lite::invalid_register_exception const& e)
	{
		std::cout << e.what() << " [Register: " << e.register_index() << ",  PC: " << e.where() << "]." << std::endl;
	}
	catch (lite::invalid_instruction_exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}