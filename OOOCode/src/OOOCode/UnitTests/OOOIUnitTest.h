#ifndef OOOIUnitTest_H
#define OOOIUnitTest_H

#include "OOOCode.h"
#include "OOOUnitTestReporter.h"

#define OOOInterface OOOIUnitTest
OOOVirtuals
	OOOVirtual(void, run, OOOUnitTestReporter * pReporter);
	OOOVirtual(char *, getName);
	OOOVirtual(void, destroy);
OOOVirtualsEnd
#undef OOOInterface

#endif
