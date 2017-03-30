#include <iostream>
#include <fstream>
#include <lite_vm.h>

class example_observer : public lite::machine_observer
{
public:
	virtual void on_register_write(const lite::word pRegister, const lite::word pValue)
	{
		std::cout << "Written " << pValue << " into register " << "[R" << pRegister << "]." << std::endl;
	}
	virtual void on_memory_write(const lite::word pAddress, const lite::word pValue)
	{
		std::cout << "Written " << pValue << " on memory address " << "[" << pAddress << "]." << std::endl;
	}
};

int main(int argc, char** argv)
{
	std::ifstream exampleSourceStream("example_program.ass");
	std::vector<lite::word> exampleProgram = lite::compiler::compile(exampleSourceStream);

	lite::virtual_machine virtualMachine(8, 512, exampleProgram);

	example_observer o;
	virtualMachine.add_observer(&o);

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