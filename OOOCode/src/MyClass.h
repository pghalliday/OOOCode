#ifndef MyClass_H
#define MyClass_H

#include "OOOCode.h"
#include "IMyInterface.h"

OOOInterface(IMyClass)
	OOOInterfaceMethod(char *, anotherMethod, char * szFormat, int nArgument);
OOOInterfaceEnd

OOOExportClass(MyClass, int nMyField);

OOOExportMethod(MyClass, int, getMyField);
OOOExportMethod(MyClass, void, setMyField, int nMyField);

OOOExportCast(MyClass, IMyClass);
OOOExportCast(MyClass, IMyInterface);

#endif
