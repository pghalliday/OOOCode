#include "UnitTests.h"

#define OOOClass UnitTests

OOOPrivateData
	UnitTestReporter * pReporter;
	IUnitTest * iTest;
	char * szName;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOF(szName))
	{
		O_free(OOOF(szName));
	}
}
OOODestructorEnd

OOOMethod(void, addTest, char * szName, IUnitTest * iTest)
{
	assert(szName);
	assert(iTest);
	OOOF(iTest) = iTest;
	if (OOOF(szName))
	{
		O_free(OOOF(szName));
	}
	OOOF(szName) = O_strdup(szName);
}
OOOMethodEnd

OOOMethod(void, runAll)
{
	OOOCall(OOOF(pReporter), startReport);
	OOOCall(OOOF(pReporter), startTestReport, OOOF(szName));
	OOOICall(OOOF(iTest), run, OOOF(pReporter));
	OOOCall(OOOF(pReporter), endTestReport);
	OOOCall(OOOF(pReporter), endReport);
}
OOOMethodEnd

OOOConstructor(UnitTestReporter * pReporter)
{
	OOOMapMethods
		OOOMethodMapping(addTest),
		OOOMethodMapping(runAll)
	OOOMapMethodsEnd

	OOOField(OOOThis, pReporter) = pReporter;
}
OOOConstructorEnd

#undef OOOClass
