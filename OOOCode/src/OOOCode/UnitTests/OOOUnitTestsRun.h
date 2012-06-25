#ifndef OOOUnitTestsRun_H
#define OOOUnitTestsRun_H

#include "OOOPastingAndQuoting.h"

#include "OOOUnitTests.h"
#include "OOOOutputDebug.h"

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
	OOOOutputDebug * pOutput = OOOConstruct(OOOOutputDebug);
	OOOUnitTestReporter * pReporter = OOOConstruct(OOOUnitTestReporter, OOOCast(OOOIOutput, pOutput));
	OOOUnitTests * pTests = OOOConstruct(OOOUnitTests, pReporter, aTests);
	OOOCall(pTests, run);
	OOODestroy(pTests);
	OOODestroy(pReporter);
	OOODestroy(pOutput);

	/* Destroy the test instances */
	while (*pTest)
	{
		OOOICall(*pTest, destroy);
		pTest++;
	}
}

#endif
