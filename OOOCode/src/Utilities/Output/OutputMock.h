#ifndef OutputMock_H
#define OutputMock_H

#include "OOOCode.h"
#include "IOutput.h"

#define OOOClass OutputMock
OOODeclare()
	OOOImplements
		OOOImplement(IOutput);
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, check, char * szCompare, ...);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
