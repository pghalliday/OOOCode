#ifndef MyClass_H
#define MyClass_H

#include "IMyInterface.h"

#include "OOOCode.h"

#define OOOInterfaceName IMyClass
OOOInterface
	OOOVirtual(char *, anotherMethod, char * szFormat, int nArgument);
OOOInterfaceEnd
#undef OOOInterfaceName

#define OOOClassName MyClass
OOOClass(int nMyField)
	OOOImplement(IMyClass);
	OOOImplement(IMyInterface);
OOOMethods
	OOOMethod(int, getMyField);
	OOOMethod(void, setMyField, int nMyField);
OOOClassEnd
#undef OOOClassName

#endif
