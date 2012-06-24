#ifndef OOOUnitTests_H
#define OOOUnitTests_H

#include "OOOCode.h"
#include "OOOUnitTestReporter.h"
#include "OOOIUnitTest.h"

#define OOOClass OOOUnitTests
OOODeclare(OOOUnitTestReporter * pReporter, OOOIUnitTest ** aTests)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, run);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
