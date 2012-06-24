#ifndef OOOUnitTestsRun_H
#define OOOUnitTestsRun_H

#include "OOOUnitTests.h"
#include "OOOOutputDebug.h"

/* Declare the test classes */
#define OOOTest(NAME) \
	_OOODeclare(NAME, char * szName) \
		OOOImplements \
			OOOImplement(OOOIUnitTest); \
		_OOOImplementsEnd(NAME) \
		OOOExports \
		_OOOExportsEnd(NAME) \
	_OOODeclareEnd(NAME)
#include "OOOTests.h"
#undef OOOTest

static void OOOUnitTestsRun(void)
{
	OOOIUnitTest * aTests[] =
	{
		/* add the test instances */
#define OOOTest(NAME) OOOCast(OOOIUnitTest, OOOConstruct(NAME, OOOQuote(NAME))),
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
