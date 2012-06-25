#include "OOOUnitTestDefines.h"
#include "OOOCode.h"

#define OOOInterface ITest
OOOVirtuals
	OOOVirtual(int, addSome, int nValue);
OOOVirtualsEnd
#undef OOOInterface

#define OOOClass Test
OOODeclare(int nValue)
	OOOImplements
		OOOImplement(ITest);
	OOOImplementsEnd
	OOOExports
		OOOExport(int, getValue);
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

OOOMethod(int, addSome, int nValue)
	return nValue + OOOC(getValue);
OOOMethodEnd

OOOConstructor(int nValue)
#define OOOInterface ITest
	OOOMapVirtuals
		OOOVirtualMapping(addSome)
	OOOMapVirtualsEnd
#undef OOOInterface
	OOOMapMethods
		OOOMethodMapping(getValue)
	OOOMapMethodsEnd
	OOOF(nValue) = nValue;
OOOConstructorEnd

#undef OOOClass

OOOTest(OOOCode)
{
	Test * pTest = OOOConstruct(Test, 5);
	OOOCheck(OOOCall(pTest, getValue) == 5);
	OOOCheck(OOOICall(OOOCast(ITest, pTest), addSome, 6) == 11);
	OOODestroy(pTest);
}
