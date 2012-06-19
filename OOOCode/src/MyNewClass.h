#ifndef MyNewClass_H
#define MyNewClass_H

#include "OOOCode.h"
#include "MyNewInterface.h"

OOOInterface(AnotherInterface)
	OOOMethod(char *, anotherMethod, char * szFormat, int nArgument);
OOOEndInterface

OOOExportClass(MyNewClass, int nMyField)
OOOExportCast(MyNewClass, AnotherInterface)
OOOExportCast(MyNewClass, MyNewInterface)

#endif
