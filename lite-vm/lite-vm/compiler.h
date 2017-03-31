#ifndef LITE_COMPILER_H
#define LITE_COMPILER_H

#include <istream>
#include <map>
#include <vector>

#include "types.h"

namespace lite
{
	struct compiler_label_request
	{
	public:
		compiler_label_request(std::string pLabel, size_t pLine, word pAddress);

		std::string mLabel;
		size_t mLine;
		word mAddress;		
	};

	class compiler
	{
	public:
		std::vector<word> compile(std::istream& pStream);

		void request_label_address(const std::string pLabel, const word pAddress);

		word current_word() const;
	private:
		size_t mCurrentLine;
		word mCurrentWord;

		std::map<std::string, word> mLabels;
		std::vector<compiler_label_request> mLabelRequests;
	};
}

#endif