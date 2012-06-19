#ifndef MyInterface_H
#define MyInterface_H

#include "OOOCode.h"

OOOInterface(IMyInterface)
	OOOInterfaceMethod(int, myMethod, int nArgument);
OOOInterfaceEnd

static inline int IMyInterface_myMethod(IMyInterface * iThis, int nArgument)
{
	assert(iThis);
	assert(iThis->myMethod);
	return iThis->myMethod(iThis->pInstance, nArgument);
}

#endif
