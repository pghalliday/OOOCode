#include "OOOUnitTestDefines.h"
#include "OOOCode2.h"

/*
 * Test interface
 */
OOOInterface2(
	ITest,
	OOOVirtual2(int, addSome, int nValue)
)

/*
 * Test class
 */
OOOClass2(
	Test,
	OOOConstructor2(int nValue),
	OOOImplements2(ITest),
	OOOExport2(int, getValue)
)

OOOClass2(
	Test,
	OOOMapVirtuals2(ITest, addSome),
	OOOMapExports2(getValue),
	OOOPrivateData2(
		int nValue
	),
	OOOConstructor2(OOOArgs2(int nValue),
		OOOF(nValue) = nValue;
	),
	OOODestructor2(
	),
	OOOMethod2(int, getPrivateValue, OOOArgs2(),
		return OOOF(nValue);
	),
	OOOMethod2(int, getValue, OOOArgs2(),
		return OOOF(nValue);
	),
	OOOMethod2(int, addSome, OOOArgs2(int nValue),
		return nValue + OOOC(getValue);
	)
)

OOOMethod2(Test, int, getValue)
{
	return OOOF(nValue);
}

OOOMethod2(Test, int, addSome, int nValue)
{
	return nValue + OOOC(getValue);
}

OOOConstructor2(Test, int nValue)
{
	OOOF(nValue) = nValue;
}

OOOTest(OOOCode2)
{
	Test * pTest = OOOConstruct(Test, 5);

	OOOCheck(OOOCall(pTest, getValue) == 5);
	OOOCheck(OOOICall(OOOCast(ITest, pTest), addSome, 6) == 11);
	/* let's see what happens when we pass a macro into a variadic macro's argument list */
	OOOCheck(OOOICall(OOOCast(ITest, pTest), addSome, OOOICall(OOOCast(ITest, pTest), addSome, 6)) == 16);
	/* now let's see what happens when we pass a variadic macro with no variadic arguments into a variadic macro's argument list */
	OOOCheck(OOOICall(OOOCast(ITest, pTest), addSome, OOOICall(OOOCast(ITest, pTest), addSome, OOOCall(pTest, getValue))) == 15);
	/* Private classes should be able to call private methods on each other directly */
	OOOCheck(OOOPCCall(Test, pTest, getPrivateValue) == 5);

	OOODestroy(pTest);
}
