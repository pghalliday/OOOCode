#include "OOOUnitTestDefines.h"

#include "OOOCode_Interface2.h"
//#include "OOOCode_ClassHeader2.h"
#include "OOOPaste.h"
#include "OOOFilter.h"
#include "OOOPre.h"
#include "OOOForEachList.h"
#include "OOOIsEmpty.h"

#define OOOConstructor2Label	1
#define OOOImplement2Label		1
#define OOOExport2Label			1

#define OOOConstructor2(ARGS...)	OOOList(OOOConstructor2Label,ARGS)
#define OOOImplement2(ARGS...)	OOOList(OOOImplement2Label,ARGS)
#define OOOExport2(ARGS...)	OOOList(OOOExport2Label,ARGS)

#define OOOClassDeclare2ConstructorType0(NAME,ARGS...) \
	typedef NAME * (* OOOPaste(NAME,_constructor))(ARGS);
#define OOOClassDeclare2ConstructorType1(NAME,ARGS...) \
	typedef NAME * (* OOOPaste(NAME,_constructor))(void);
#define OOOClassDeclare2ConstructorType(NAME,ARGS...) OOOPaste(OOOClassDeclare2ConstructorType,OOOIsEmpty(ARGS))(NAME,ARGS)

// Private class stuff
//	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct(ARGS)) GCCO_SAFE_DS; \
//	static OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct);
//	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(void) GCCO_SAFE_DS; \
//	static OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct);

#define OOOClassDeclare2(NAME,ARGS...) \
	typedef struct OOOPaste(_,NAME) NAME; \
	OOOClassDeclare2ConstructorType(NAME,OOOPre(OOOFilter(OOOConstructor2Label,ARGS))) \
	extern OOOPaste(NAME,_constructor) OOOPaste(NAME,_construct); \
	typedef struct \
	{ \
		NAME OOOPaste(t,NAME); \
	} \
	OOOPaste(NAME,_Interfaces); \
	typedef struct \
	{ \
		void (* destroy)(NAME * OOOThis); \
		RETURN (* NAME)(CLASS_NAME * OOOThis, ARGS); \
		RETURN (* NAME)(CLASS_NAME * OOOThis); \
	} \
	OOOPaste(NAME,_VTable); \
	struct OOOPaste(_,NAME) \
	{ \
		OOOPaste(NAME,_VTable) * pVTable; \
		OOOPaste(NAME,_Interfaces) tInterfaces; \
	};

// Private method forward declarations (don't think we'll need these as all
// methods can be forward declared by default using this style)
//	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis, ARGS) GCCO_SAFE_DS;
//	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis) GCCO_SAFE_DS;

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
