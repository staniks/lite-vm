#include <regex>
#include <string>

#include "compiler.h"
#include "exception.h"
#include "instruction_set.h"

using namespace lite;

compiler_label_request::compiler_label_request(std::string pLabel, size_t pLine, word pAddress)
	:
	mLabel(pLabel),
	mLine(pLine),
	mAddress(pAddress)
{

}

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
		auto request = *it;

		auto labelIterator = mLabels.find(request.mLabel);
		if (labelIterator == mLabels.end())
			throw compiler_exception(request.mLine);

		words[request.mAddress] = labelIterator->second;		
	}

	return words;
}
void compiler::request_label_address(const std::string pLabel, const word pAddress)
{
	mLabelRequests.push_back(compiler_label_request(pLabel, mCurrentLine, pAddress));
}

word compiler::current_word() const
{
	return mCurrentWord;
}