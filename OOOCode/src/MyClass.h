#ifndef MyClass_H
#define MyClass_H

#include "IMyInterface.h"

#include "OOOCode.h"

#define OOOClassName MyClass
OOOClass(int nMyField)
	OOOImplement(IMyInterface);
OOOExports
	OOOExport(int, getMyField);
	OOOExport(void, setMyField, int nMyField);
OOOClassEnd
#undef OOOClassName

#endif
