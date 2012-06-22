#ifndef UnitTests_H
#define UnitTests_H

#include "OOOCode.h"
#include "UnitTestReporter.h"
#include "IUnitTest.h"

#define OOOClass UnitTests
OOODeclare(UnitTestReporter * pReporter)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, addTest, char * szName, IUnitTest * iTest);
		OOOExport(void, runAll);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
