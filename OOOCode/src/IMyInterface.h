#ifndef MyInterface_H
#define MyInterface_H

#include "OOOCode.h"

#define OOOInterface IMyInterface
OOOVirtuals
	OOOVirtual(int, myMethod, int nArgument);
OOOVirtualsEnd
#undef OOOInterface

#endif
