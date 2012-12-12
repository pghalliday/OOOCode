#include "OOOUnitTestDefines.h"

#include "OOOCode_Interface2.h"
#include "OOOCode_ClassHeader2.h"

#define OOODeclareStruct(CLASS_NAME) \
	typedef struct OOOPaste(_, CLASS_NAME) CLASS_NAME;
#define OOODeclareConstructorType0(CLASS_NAME, ARGS...) \
	typedef CLASS_NAME * (* OOOPaste(CLASS_NAME, _constructor))(ARGS);
#define OOODeclareConstructorType1(CLASS_NAME) \
	typedef CLASS_NAME * (* OOOPaste(CLASS_NAME, _constructor))(void);
#define OOODeclare0OOOPublic(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType0(CLASS_NAME, ARGS) \
	extern OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct);
#define OOODeclare1OOOPublic(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType1(CLASS_NAME) \
	extern OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct);
#define OOODeclare0OOOPrivate(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType0(CLASS_NAME, ARGS) \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct(ARGS)) GCCO_SAFE_DS; \
	static OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct);
#define OOODeclare1OOOPrivate(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType1(CLASS_NAME) \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(void) GCCO_SAFE_DS; \
	static OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct);
#define __OOODeclare(SCOPE, CLASS_NAME, ARGS...) OOOPaste(OOODeclare, OOOIsEmpty(ARGS), SCOPE)(CLASS_NAME, ARGS)
#define _OOODeclare(CLASS_NAME, ARGS...) __OOODeclare(OOOPublic, CLASS_NAME, ARGS)
#define OOODeclare(ARGS...) _OOODeclare(OOOClass, ARGS)
#define OOODeclarePrivate(ARGS...) __OOODeclare(OOOPrivate, OOOClass, ARGS)

/*
 * Export Interfaces
 */

/* Start the interfaces structure */
#define OOOImplements \
	typedef struct \
	{

/* Add an interface */
#define OOOImplement(INTERFACE_NAME) \
		INTERFACE_NAME OOOPaste(t, INTERFACE_NAME);

/* End the interfaces structure and declare the type name */
#define _OOOImplementsEnd(CLASS_NAME) \
	} \
	OOOPaste(CLASS_NAME, _Interfaces);
#define OOOImplementsEnd _OOOImplementsEnd(OOOClass)

/*
 * Export methods
 */

/* start the vtable structure */
#define _OOOExports(CLASS_NAME) \
	typedef struct \
	{ \
		void (* destroy)(CLASS_NAME * OOOThis);
#define OOOExports _OOOExports(OOOClass)

/* add an exported method */
#define OOOExport0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(CLASS_NAME * OOOThis, ARGS);
#define OOOExport1(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(CLASS_NAME * OOOThis);
#define _OOOExport(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(OOOExport, OOOIsEmpty(ARGS))(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOExport(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOExport(OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)

/* end the vtable structure and declare the type name */
#define _OOOExportsEnd(CLASS_NAME) \
	} \
	OOOPaste(CLASS_NAME, _VTable);
#define OOOExportsEnd _OOOExportsEnd(OOOClass)

/*
 * End the class declaration and define the public structure
 */

#define _OOODeclareEnd(CLASS_NAME) \
	struct OOOPaste(_, CLASS_NAME) \
	{ \
		OOOPaste(CLASS_NAME, _VTable) * pVTable; \
		OOOPaste(CLASS_NAME, _Interfaces) tInterfaces; \
	};
#define OOODeclareEnd _OOODeclareEnd(OOOClass)

/* forward declare a function to be used in private calls */
#define _OOOPCDeclare0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis, ARGS) GCCO_SAFE_DS;
#define _OOOPCDeclare1(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis) GCCO_SAFE_DS;
#define _OOOPCDeclare(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(_OOOPCDeclare, OOOIsEmpty(ARGS))(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOPCDeclare(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOPCDeclare(OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)


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
OOOClassDeclare2(
	Test,
	OOOConstructor2(int nValue),
	OOOImplement2(ITest),
	OOOExport2(int, getValue)
)

OOOClassImplement2(
	Test,
	OOOImplement2(ITest, addSome),
	OOOExport2(getValue),
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
