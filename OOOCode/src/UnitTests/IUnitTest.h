#ifndef IUnitTest_H
#define IUnitTest_H

#include "OOOCode.h"
#include "UnitTestReporter.h"

#define OOOInterface IUnitTest
OOOVirtuals
	OOOVirtual(void, run, UnitTestReporter * pReporter);
OOOVirtualsEnd
#undef OOOInterface

#endif
