#include <regex>
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
	word currentWord = 0;

	mLabels.clear();

	mCurrentLine = 1;
	while (std::getline(pStream, line))
	{
		std::vector<word> instructionWords = instructionSet.compile(*this, line);

		if (instructionWords.size() == 0)
		{
			//if it's not an instruction, maybe it's a label
			std::regex regex("^([a-z]+):$", std::regex_constants::extended);
			std::smatch match;
			if (std::regex_search(line, match, regex))
			{
				mLabels[match[1].str()] = currentWord;
			}
			else
				throw compiler_exception(mCurrentLine);
		}	

		for (size_t i = 0; i < instructionWords.size(); i++)
			words.push_back(instructionWords[i]);

		++mCurrentLine;
		currentWord += (word)instructionWords.size();
	}

	return words;
}
word compiler::label(const std::string pLabel) const
{
	auto it = mLabels.find(pLabel);
	if (it == mLabels.end())
		throw compiler_exception(mCurrentLine);

	return it->second;
}