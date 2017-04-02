#include "compilation_process.h"

using namespace lite;

compiler_label_request::compiler_label_request(std::string pLabel, size_t pLine, word pAddress)
	:
	mLabel(pLabel),
	mLine(pLine),
	mAddress(pAddress)
{

}

compilation_process::compilation_process()
	:
	mCurrentLine(1),
	mCurrentWord(0)
{
	
}
void compilation_process::request_label_address(const std::string pLabel, const word pAddress)
{
	mLabelRequests.push_back(compiler_label_request(pLabel, mCurrentLine, pAddress));
}
size_t compilation_process::current_line() const
{
	return mCurrentLine;
}
word compilation_process::current_word() const
{
	return mCurrentWord;
}