#include <regex>
#include <string>

#include "compiler.h"
#include "compilation_process.h"
#include "exception.h"
#include "instruction_set.h"

using namespace lite;

std::vector<word> compiler::compile(std::istream& pStream)
{
	instruction_set instructionSet;
	std::vector<word> words;
	std::string line;

	compilation_process compilationProcess;

	while (std::getline(pStream, line))
	{
		//trim the line
		line = lite::trim(line);

		std::vector<word> instructionWords = instructionSet.compile(compilationProcess, line);

		if (instructionWords.size() == 0)
		{
			//if it's not an instruction, maybe it's a label
			std::regex regex("^([a-z]+):$", std::regex_constants::extended);
			std::smatch match;
			if (std::regex_search(line, match, regex))
			{
				compilationProcess.mLabels[match[1].str()] = compilationProcess.mCurrentWord;
			}
			else
				throw compiler_exception(compilationProcess.mCurrentLine, "Invalid instruction \"" + line + "\".");
		}	

		for (size_t i = 0; i < instructionWords.size(); i++)
			words.push_back(instructionWords[i]);

		++compilationProcess.mCurrentLine;
		compilationProcess.mCurrentWord += (word)instructionWords.size();
	}

	//go through the label requests
	for (auto it = compilationProcess.mLabelRequests.begin(); it != compilationProcess.mLabelRequests.end(); it++)
	{
		auto request = *it;

		auto labelIterator = compilationProcess.mLabels.find(request.mLabel);
		if (labelIterator == compilationProcess.mLabels.end())
			throw compiler_exception(request.mLine, "Unknown label \"" + request.mLabel + "\".");

		words[request.mAddress] = labelIterator->second;		
	}

	return words;
}