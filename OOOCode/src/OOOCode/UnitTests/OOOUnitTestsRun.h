#ifndef OOOUnitTestsRun_H
#define OOOUnitTestsRun_H

#include "OOOPastingAndQuoting.h"

#include "OOOUnitTests.h"
#include "OOODebug.h"
#include "OOODebugReporter.h"

/* Declare the test classes */
#define OOOTest(NAME) \
	_OOODeclare(OOOPaste(OOOUnitTest_,NAME)) \
		OOOImplements \
			OOOImplement(OOOIUnitTest); \
		_OOOImplementsEnd(OOOPaste(OOOUnitTest_,NAME)) \
		OOOExports \
		_OOOExportsEnd(OOOPaste(OOOUnitTest_,NAME)) \
	_OOODeclareEnd(OOOPaste(OOOUnitTest_,NAME))
#include "OOOTests.h"
#undef OOOTest

static void OOOUnitTestsRun(void)
{
	OOOIUnitTest * aTests[] =
	{
		/* add the test instances */
#define OOOTest(NAME) OOOCast(OOOIUnitTest, OOOConstruct(OOOPaste(OOOUnitTest_,NAME))),
#include "OOOTests.h"
#undef OOOTest
		NULL
	};
	OOOIUnitTest ** pTest = aTests;
	OOODebug * pDebug = OOOConstruct(OOODebug);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOIDebug, pDebug));
	OOOUnitTests * pTests = OOOConstruct(OOOUnitTests, OOOCast(OOOIReporter, pReporter), aTests);
	OOOCall(pTests, run);
	OOODestroy(pTests);
	OOODestroy(pReporter);
	OOODestroy(pDebug);

	/* Destroy the test instances */
	while (*pTest)
	{
		OOOICall(*pTest, destroy);
		pTest++;
	}
}

#endif
