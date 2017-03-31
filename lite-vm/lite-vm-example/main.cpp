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
	virtual void on_compare_flag_write(const lite::word pValue)
	{
		std::cout << "Written " << pValue << " in compare flag register." << std::endl;
	}
};

int main(int argc, char** argv)
{
	std::ifstream exampleSourceStream("example_program.ass");
	std::vector<lite::word> exampleProgram;
	
	lite::compiler compiler;
	try
	{
		exampleProgram = compiler.compile(exampleSourceStream);
	}
	catch (const lite::compiler_exception& e)
	{
		std::cout << e.what() << " Line: " << e.line() << std::endl;
		return 1;
	}

	lite::virtual_machine virtualMachine(8, 512, exampleProgram);

	example_observer o;
	virtualMachine.add_observer(&o);

	try
	{
		while (virtualMachine.step());
	}	
	catch (const lite::invalid_address_exception& e)
	{
		std::cout << e.what() << " [Address: " << e.address() << ",  PC: " << e.where() << "]." << std::endl;
	}
	catch (const lite::invalid_register_exception& e)
	{
		std::cout << e.what() << " [Register: " << e.register_index() << ",  PC: " << e.where() << "]." << std::endl;
	}
	catch (const lite::invalid_instruction_exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}