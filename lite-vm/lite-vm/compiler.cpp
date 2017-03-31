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
	
	mLabelRequests.clear();
	mLabels.clear();

	mCurrentLine = 1;
	mCurrentWord = 0;
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
				mLabels[match[1].str()] = mCurrentWord;
			}
			else
				throw compiler_exception(mCurrentLine);
		}	

		for (size_t i = 0; i < instructionWords.size(); i++)
			words.push_back(instructionWords[i]);

		++mCurrentLine;
		mCurrentWord += (word)instructionWords.size();
	}

	//go through the label requests
	for (auto it = mLabelRequests.begin(); it != mLabelRequests.end(); it++)
	{
		auto pair = *it;
		words[pair.second] = label(pair.first);		
	}

	return words;
}
void compiler::request_label_address(const std::string pLabel, const word pAddress)
{
	mLabelRequests.push_back(std::pair<std::string, word>(pLabel, pAddress));
}

word compiler::current_word() const
{
	return mCurrentWord;
}

word compiler::label(const std::string pLabel) const
{
	auto it = mLabels.find(pLabel);
	if (it == mLabels.end())
		throw compiler_exception(mCurrentLine);

	return it->second;
}