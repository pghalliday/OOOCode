#ifndef OutputDebug_H
#define OutputDebug_H

#include "OOOCode.h"
#include "IOutput.h"

#define OOOClass OutputDebug
OOODeclare()
	OOOImplements
		OOOImplement(IOutput);
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
