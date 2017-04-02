#ifndef LITE_COMPILATION_PROCESS_H
#define LITE_COMPILATION_PROCESS_H

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

	class compilation_process
	{
		friend class compiler;
	public:
		compilation_process();
		void request_label_address(const std::string pLabel, const word pAddress);

		size_t current_line() const;
		word current_word() const;
	private:
		size_t mCurrentLine;
		word mCurrentWord;
		std::map<std::string, word> mLabels;
		std::vector<compiler_label_request> mLabelRequests;
	};
}

#endif