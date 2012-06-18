#ifndef MyNewClass_H
#define MyNewClass_H

#include "OOOCode.h"
#include "MyNewInterface.h"

BEGIN_INTERFACE
	INTERFACE_METHOD(char *, anotherMethod, char * szFormat, int nArgument)
END_INTERFACE(AnotherInterface)

CLASS(MyNewClass, int nMyField)
EXPOSE_INTERFACE(MyNewClass, AnotherInterface)
EXPOSE_INTERFACE(MyNewClass, MyNewInterface)

#endif
