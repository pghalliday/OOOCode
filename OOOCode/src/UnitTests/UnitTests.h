#ifndef UnitTests_H
#define UnitTests_H

#include "OOOCode.h"
#include "UnitTestReporter.h"
#include "IUnitTest.h"

#define OOOClass UnitTests
OOODeclare(UnitTestReporter * pReporter, IUnitTest ** aTests)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, run);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
