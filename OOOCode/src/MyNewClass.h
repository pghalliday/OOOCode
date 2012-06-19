#ifndef MyNewClass_H
#define MyNewClass_H

#include "OOOCode.h"
#include "MyNewInterface.h"

OOOC_Interface
	char * OOOC_Method(anotherMethod, char * szFormat, int nArgument);
OOOC_EndInterface(AnotherInterface)

OOOC_ExportClass(MyNewClass, int nMyField)
OOOC_ExportCast(MyNewClass, AnotherInterface)
OOOC_ExportCast(MyNewClass, MyNewInterface)

#endif
