#ifndef IOutput_H
#define IOutput_H

#include "OOOCode.h"

#define OOOInterface IOutput
OOOVirtuals
	OOOVirtual(void, print, char * szMessage, ...);
OOOVirtualsEnd
#undef OOOInterface

#endif
