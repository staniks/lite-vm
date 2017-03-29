#ifndef LITE_MEMORY_LISTENER_H
#define LITE_MEMORY_LISTENER_H

#include "types.h"

namespace lite
{
	class machine_observer
	{
	public:
		virtual void on_register_write(word pRegister, word pValue) = 0;
		virtual void on_memory_write(word pAddress, word pValue) = 0;
	};
}

#endif