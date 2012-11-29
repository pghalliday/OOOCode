#include "OOOUnitTestDefines.h"
#include "OOOCode.h"

/*
 * Test private class
 */
#define OOOClass TestPrivate
OOODeclarePrivate(int nValue)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(int, getValue)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	int nValue;
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(int, getValue)
	return OOOF(nValue);
OOOMethodEnd

OOOConstructorPrivate(int nValue)
	OOOMapMethods
		OOOMapMethod(getValue)
	OOOMapMethodsEnd
	OOOF(nValue) = nValue;
OOOConstructorEnd
#undef OOOClass

OOOTest(OOOCodePrivate)
{
	TestPrivate * pTestPrivate = OOOConstruct(TestPrivate, 5);
	OOOCheck(OOOCall(pTestPrivate, getValue) == 5);
	OOODestroy(pTestPrivate);
}
