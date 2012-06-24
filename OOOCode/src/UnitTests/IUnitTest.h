#ifndef IUnitTest_H
#define IUnitTest_H

#include "OOOCode.h"
#include "UnitTestReporter.h"

#define OOOInterface IUnitTest
OOOVirtuals
	OOOVirtual(void, run, UnitTestReporter * pReporter);
	OOOVirtual(char *, getName);
	OOOVirtual(void, destroy);
OOOVirtualsEnd
#undef OOOInterface

#endif
