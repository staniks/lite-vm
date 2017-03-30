#ifndef LITE_MEMORY_LISTENER_H
#define LITE_MEMORY_LISTENER_H

#include "types.h"

namespace lite
{
	class machine_observer
	{
	public:
		virtual void on_register_write(const word pRegister, const word pValue) = 0;
		virtual void on_memory_write(const word pAddress, const word pValue) = 0;
	};
}

#endif