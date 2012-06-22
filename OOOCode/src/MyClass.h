#ifndef MyClass_H
#define MyClass_H

#include "OOOCode.h"
#include "IMyInterface.h"

#define OOOClass MyClass
OOODeclare(int nMyField)
	OOOImplements
		OOOImplement(IMyInterface);
	OOOImplementsEnd
	OOOExports
		OOOExport(int, getMyField);
		OOOExport(void, setMyField, int nMyField);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
