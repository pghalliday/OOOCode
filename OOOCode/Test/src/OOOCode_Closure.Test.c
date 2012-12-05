#include "OOOUnitTestDefines.h"

#define TEST_CLOSURE_DATA_1	10
#define TEST_STRING			"This is a test"
#define TEST_NUMBER			100
#define TEST_CLOSURE_DATA_2	"This is also a test"

#define OOOInterface ITest1
OOOVirtuals
	OOOVirtual(int, getNumber)
	OOOVirtual(char *, getString)
	OOOVirtual(void, values, char * szString, int nNumber)
OOOVirtualsEnd
#undef OOOInterface

#define OOOInterface ITest2
OOOVirtuals
	OOOVirtual(void, values)
OOOVirtualsEnd
#undef OOOInterface

#define OOOClass TestTarget
OOODeclarePrivate()
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, close1, ITest1 * iTest1)
		OOOExport(void, close2, ITest2 * iTest2)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, close1, ITest1 * iTest1)
{
	OOOICall(iTest1, values, OOOICall(iTest1, getString), OOOICall(iTest1, getNumber));
}
OOOMethodEnd

OOOMethod(void, close2, ITest2 * iTest2)
{
	OOOICall(iTest2, values);
}
OOOMethodEnd

OOOConstructorPrivate()
{
	OOOMapMethods
		OOOMapMethod(close1)
		OOOMapMethod(close2)
	OOOMapMethodsEnd
}
OOOConstructorEnd
#undef OOOClass

#define OOOClass Test
OOODeclarePrivate()
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

#define OOOClosure TestClosure1
#define OOOClosureType short

#define OOOClosureInterface ITest1
#define OOOClosureInputs int, char *
#define OOOClosureOutputs char *, int
#include "OOOCode_Closure.h"
#undef OOOClosureOutputs
#undef OOOClosureInputs
#undef OOOClosureInterface

#undef OOOClosureType
#undef OOOClosure

// This closure tests empty argument lists on input and output
#define OOOClosure TestClosure2
#define OOOClosureType char *

#define OOOClosureInterface ITest2
#define OOOClosureInputs
#define OOOClosureOutputs
#include "OOOCode_Closure.h"
#undef OOOClosureOutputs
#undef OOOClosureInputs
#undef OOOClosureInterface

#undef OOOClosureType
#undef OOOClosure

OOOPrivateData
	TestTarget * pTestTarget;
	bool bChecked1;
	bool bChecked2;
OOOPrivateDataEnd

OOODestructor
{
	OOODestroy(OOOF(pTestTarget));
}
OOODestructorEnd

OOOMethod(void, values1, short nClosureData, char * szString, int nNumber)
{
	OOOCheck(nClosureData == TEST_CLOSURE_DATA_1);
	if (O_strcmp(szString, TEST_STRING) != 0)
	{
		OOOError("Expected: %s: Received: %s", TEST_STRING, szString);
	}
	OOOCheck(nNumber == TEST_NUMBER);
	OOOF(bChecked1) = TRUE;
}
OOOMethodEnd

OOOMethod(void, values2, char * szClosureData)
{
	if (O_strcmp(szClosureData, TEST_CLOSURE_DATA_2) != 0)
	{
		OOOError("Expected: %s: Received: %s", TEST_STRING, szClosureData);
	}
	OOOF(bChecked2) = TRUE;
}
OOOMethodEnd

OOOMethod(void, start)
{
	TestClosure1 * pClosure1;
	TestClosure2 * pClosure2;

	pClosure1 = OOOClosureConstruct
	(
		TestClosure1,
		values1,
		TEST_CLOSURE_DATA_1,
		TEST_NUMBER,
		TEST_STRING
	);
	OOOCall(OOOF(pTestTarget), close1, OOOCast(ITest1, pClosure1));
	OOOCheck(OOOF(bChecked1));

	pClosure2 = OOOClosureConstruct
	(
		TestClosure2,
		values2,
		TEST_CLOSURE_DATA_2
	);
	OOOCall(OOOF(pTestTarget), close2, OOOCast(ITest2, pClosure2));
	OOOCheck(OOOF(bChecked2));
}
OOOMethodEnd

OOOConstructorPrivate()
{
	OOOMapMethods
		OOOMapMethod(start)
	OOOMapMethodsEnd

	OOOF(pTestTarget) = OOOConstruct(TestTarget);
}
OOOConstructorEnd
#undef OOOClass

OOOTest(OOOCode_Closure)
{
	Test * pTest = OOOConstruct(Test);
	OOOCall(pTest, start);
	OOODestroy(pTest);
}
