#include <string>

#include "compiler.h"
#include "exception.h"
#include "instruction_set.h"

using namespace lite;

std::vector<word> compiler::compile(std::istream& pStream)
{
	instruction_set instructionSet;
	std::vector<word> words;

	std::string line;
	uint32_t lineNumber = 1;
	while (std::getline(pStream, line))
	{
		std::vector<word> instructionWords = instructionSet.compile(line);

		if (instructionWords.size() == 0)
			throw compiler_exception(lineNumber);

		for (int i = 0; i < instructionWords.size(); i++)
			words.push_back(instructionWords[i]);

		++lineNumber;
	}

	return words;
}