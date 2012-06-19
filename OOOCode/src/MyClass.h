#ifndef MyClass_H
#define MyClass_H

#include "OOOCode.h"
#include "MyInterface.h"

OOOInterface(AnotherInterface)
	OOOMethod(char *, anotherMethod, char * szFormat, int nArgument);
OOOInterfaceEnd

OOOExportClass(MyClass, int nMyField)
OOOExportCast(MyClass, AnotherInterface)
OOOExportCast(MyClass, MyInterface)

#endif
