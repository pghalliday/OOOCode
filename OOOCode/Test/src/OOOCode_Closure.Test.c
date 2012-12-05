#include "OOOUnitTestDefines.h"

#define TEST_CLOSURE_DATA	10
#define TEST_STRING			"This is a test"
#define TEST_NUMBER			100

#define OOOInterface ITest
OOOVirtuals
	OOOVirtual(int, getNumber)
	OOOVirtual(char *, getString)
	OOOVirtual(void, values, char * szString, int nNumber)
OOOVirtualsEnd
#undef OOOInterface

#define OOOClass TestTarget
OOODeclare()
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, close, ITest * iTest)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, close, ITest * iTest)
	OOOICall(iTest, values, OOOICall(iTest, getString), OOOICall(iTest, getNumber));
OOOMethodEnd

OOOConstructor()
	OOOMapMethods
		OOOMapMethod(close)
	OOOMapMethodsEnd
OOOConstructorEnd
#undef OOOClass

#define OOOClass Test
OOODeclare()
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

#define OOOClosure TestClosure
#define OOOClosureType short

#define OOOClosureInterface ITest
#define OOOClosureInputs int, char *
#define OOOClosureOutputs char *, int
#include "OOOCode_Closure.h"
#undef OOOClosureOutputs
#undef OOOClosureInputs
#undef OOOClosureInterface

#undef OOOClosureType
#undef OOOClosure

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, values, short nClosureData, char * szString, int nNumber)
{
	OOOCheck(nClosureData == TEST_CLOSURE_DATA);
	if (O_strcmp(szString, TEST_STRING) != 0)
	{
		OOOError("Expected: %s: Received: %s", TEST_STRING, szString);
	}
	OOOCheck(nNumber == TEST_NUMBER);
}
OOOMethodEnd

OOOMethod(void, start)
	TestTarget * pTestTarget = OOOConstruct(TestTarget);
	TestClosure * pClosure = OOOClosureConstruct
	(
		TestClosure,
		values,
		TEST_CLOSURE_DATA,
		TEST_NUMBER,
		TEST_STRING
	);
	OOOCall(pTestTarget, close, OOOCast(ITest, pClosure));
OOOMethodEnd

OOOConstructor()
	OOOMapMethods
		OOOMapMethod(start)
	OOOMapMethodsEnd
OOOConstructorEnd
#undef OOOClass

OOOTest(OOOCode_Closure)
{
	Test * pTest = OOOConstruct(Test);
	OOODestroy(pTest);
}
