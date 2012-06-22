#include "UnitTests.h"

#define OOOClass UnitTests

OOOPrivateData
	UnitTestReporter * pReporter;
	IUnitTest * iTest;
	char * szName;
OOOPrivateDataEnd

OOODestructor
{
	if (OOO(szName))
	{
		O_free(OOO(szName));
	}
}
OOODestructorEnd

OOOMethod(void, addTest, char * szName, IUnitTest * iTest)
{
	assert(szName);
	assert(iTest);
	OOO(iTest) = iTest;
	if (OOO(szName))
	{
		O_free(OOO(szName));
	}
	OOO(szName) = O_strdup(szName);
}
OOOMethodEnd

OOOMethod(void, runAll)
{
	OOOCall(OOO(pReporter), startReport);
	OOOCall(OOO(pReporter), startTestReport, OOO(szName));
	OOOICall(OOO(iTest), run, OOO(pReporter));
	OOOCall(OOO(pReporter), endTestReport);
	OOOCall(OOO(pReporter), endReport);
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
