#include <string>

#include "compiler.h"
#include "instruction_set.h"

using namespace lite;

std::vector<word> compiler::compile(std::istream& pStream)
{
	instruction_set instructionSet;
	std::vector<word> words;

	std::string line;
	while (std::getline(pStream, line))
	{
		std::vector<word> instructionWords = instructionSet.compile(line);
		for (int i = 0; i < instructionWords.size(); i++)
			words.push_back(instructionWords[i]);
	}

	return words;
}