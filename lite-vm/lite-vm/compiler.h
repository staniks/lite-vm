#ifndef LITE_COMPILER_H
#define LITE_COMPILER_H

#include <istream>
#include <map>
#include <vector>

#include "types.h"

namespace lite
{
	class compiler
	{
	public:
		std::vector<word> compile(std::istream& pStream);

		void request_label_address(const std::string pLabel, const word pAddress);

		word current_word() const;
	private:
		word label(const std::string pLabel) const;

		size_t mCurrentLine;
		word mCurrentWord;

		std::map<std::string, word> mLabels;
		std::vector<std::pair<std::string, word>> mLabelRequests;
	};
}

#endif