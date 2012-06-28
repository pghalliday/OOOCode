#ifndef OOOIUnitTest_H
#define OOOIUnitTest_H

#include "OOOCode.h"
#include "OOOIReporter.h"

#define OOOInterface OOOIUnitTest
OOOVirtuals
	OOOVirtual(void, run, OOOIReporter * iReporter);
	OOOVirtual(char *, getName);
	OOOVirtual(void, destroy);
OOOVirtualsEnd
#undef OOOInterface

#endif
