#ifndef MessagePump_H
#define MessagePump_H

#include "OOOCode.h"
#include "IMessagePumpController.h"

#define OOOClass MessagePump
OOODeclare()
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start, IMessagePumpController * iMessagePumpController)
		OOOExport(void, stop)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
