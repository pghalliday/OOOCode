#ifndef UnitTestsRun_H
#define UnitTestsRun_H

#include "UnitTests.h"
#include "OutputDebug.h"

/* Declare the test classes */
#define OOOTest(NAME) \
	_OOODeclare(NAME, char * szName) \
		OOOImplements \
			OOOImplement(IUnitTest); \
		_OOOImplementsEnd(NAME) \
		OOOExports \
		_OOOExportsEnd(NAME) \
	_OOODeclareEnd(NAME)
#include "OOOTests.h"
#undef OOOTest

static void UnitTestsRun(void)
{
	IUnitTest * aTests[] =
	{
		/* add the test instances */
#define OOOTest(NAME) OOOCast(IUnitTest, OOOConstruct(NAME, QUOTE(NAME))),
#include "OOOTests.h"
#undef OOOTest
		NULL
	};
	IUnitTest ** pTest = aTests;
	OutputDebug * pOutput = OOOConstruct(OutputDebug);
	UnitTestReporter * pReporter = OOOConstruct(UnitTestReporter, OOOCast(IOutput, pOutput));
	UnitTests * pTests = OOOConstruct(UnitTests, pReporter, aTests);
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
