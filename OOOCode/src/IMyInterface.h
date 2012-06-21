#ifndef MyInterface_H
#define MyInterface_H

#include "OOOCode.h"

#define OOOInterfaceName IMyInterface
OOOInterface
	OOOVirtual(int, myMethod, int nArgument);
OOOInterfaceEnd
#undef OOOInterfaceName

#endif
