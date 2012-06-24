#include "OOOUnitTests.h"

#define OOOClass OOOUnitTests

OOOPrivateData
	OOOUnitTestReporter * pReporter;
	OOOIUnitTest ** aTests;
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, run)
{
	size_t uHeapAvailableBefore = 0;
	size_t uHeapAvailableAfter = 0;
	OOOIUnitTest ** pTest = OOOF(aTests);

	OOOCall(OOOF(pReporter), startReport);

	while (*pTest)
	{
		OOOCall(OOOF(pReporter), startTestReport, OOOICall(*pTest, getName));

		uHeapAvailableBefore = O_heap_available();
		OOOICall(*pTest, run, OOOF(pReporter));
		uHeapAvailableAfter = O_heap_available();

		if (uHeapAvailableBefore > uHeapAvailableAfter)
		{
			OOOCall(OOOF(pReporter), memoryLeak, OOOICall(*pTest, getName), uHeapAvailableBefore - uHeapAvailableAfter);
		}
		else if (uHeapAvailableAfter > uHeapAvailableBefore)
		{
			OOOCall(OOOF(pReporter), memoryMagic, OOOICall(*pTest, getName), uHeapAvailableAfter - uHeapAvailableBefore);
		}

		OOOCall(OOOF(pReporter), endTestReport);
		pTest++;
	}
	OOOCall(OOOF(pReporter), endReport);
}
OOOMethodEnd

OOOConstructor(OOOUnitTestReporter * pReporter, OOOIUnitTest ** aTests)
{
	OOOMapMethods
		OOOMethodMapping(run)
	OOOMapMethodsEnd

	OOOF(pReporter) = pReporter;
	OOOF(aTests) = aTests;
}
OOOConstructorEnd

#undef OOOClass
