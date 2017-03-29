#include "compiler.h"
#include "instruction_set.h"

using namespace lite;

std::vector<byte> compiler::compile(std::stringstream& stream)
{
	instruction_set instructionSet;
	std::vector<byte> bytes;

	std::string line;
	while (std::getline(stream, line))
	{
		std::vector<byte> instructionBytes = instructionSet.compile(line);
		for (int i = 0; i < instructionBytes.size(); i++)
			bytes.push_back(instructionBytes[i]);
	}

	return bytes;
}