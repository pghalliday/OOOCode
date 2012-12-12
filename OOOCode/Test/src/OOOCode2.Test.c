#include "OOOUnitTestDefines.h"

#include "OOOCode_Interface2.h"
#include "OOOCode_ClassHeader2.h"
//#include "OOOCode_ClassImplementation2.h"
#include "OOOPaste.h"
#include "OOOForEach.h"
#include "OOOFilter.h"
#include "OOOPre.h"
#include "OOOForEachClosure.h"
#include "OOOPreList.h"
#include "OOOPostList.h"
#include "OOOIsEmpty.h"

#define OOOPrivateData2Label	4
#define OOOConstructor2Label	5
#define OOODestructor2Label		6
#define OOOMethod2Label			7
#define OOOArgs2				8

#define OOOPrivateData2(ARGS...)	OOOList(OOOPrivateData2Label,ARGS)
#define OOOConstructor2(ARGS...)	OOOList(OOOConstructor2Label,ARGS)
#define OOODestructor2(ARGS...)		OOOList(OOODestructor2Label,ARGS)
#define OOOMethod2(ARGS...)			OOOList(OOOMethod2Label,ARGS)
#define OOOArgs2(ARGS...)			OOOList(ARGS)

#define OOOClassImplement2PrivateData(FIRST,LAST,ITERATION,FIELD,REMAINDER...) \
	FIELD; \
	REMAINDER

#define OOOClassImplement2MethodDeclare0(CLASS_NAME,RETURN,NAME,ARGS...) \
	static RETURN OOOPaste(CLASS_NAME,_,NAME)(CLASS_NAME * OOOThis, ARGS) GCCO_SAFE_DS;
#define OOOClassImplement2MethodDeclare1(CLASS_NAME,RETURN,NAME,ARGS...) \
	static RETURN OOOPaste(CLASS_NAME,_,NAME)(CLASS_NAME * OOOThis) GCCO_SAFE_DS;
#define __OOOClassImplement2MethodDeclare(CLASS_NAME,RETURN,NAME,ARGS...) OOOPaste(OOOClassImplement2MethodDeclare,OOOIsEmpty(ARGS))(CLASS_NAME,RETURN,NAME,ARGS)
#define _OOOClassImplement2MethodDeclare(CLASS_NAME,ARGS...) __OOOClassImplement2MethodDeclare(CLASS_NAME,ARGS)
#define OOOClassImplement2MethodDeclare(FIRST,LAST,ITERATION,CLOSURE_LIST_REMAINDER...) \
	_OOOClassImplement2MethodDeclare(OOOPreList(0,CLOSURE_LIST_REMAINDER),OOOPreList(1,CLOSURE_LIST_REMAINDER)) \
	OOOPostList(1,CLOSURE_LIST_REMAINDER)

#define OOOClassImplement2MethodBody(BODY...) \
	{ \
		assert(OOOThis); \
		{ \
			BODY \
		} \
	}
#define OOOClassImplement2Method0(CLASS_NAME,RETURN,NAME,ARGS...) \
	typedef RETURN (* OOOPaste(OOOVirtual_,CLASS_NAME,_,NAME))(void * OOOThis, OOOPre(ARGS)); \
	static RETURN OOOPaste(CLASS_NAME, _,NAME)(CLASS_NAME * OOOThis, OOOPre(ARGS)) \
	OOOClassImplement2MethodBody(OOOPost(ARGS))
#define OOOClassImplement2Method1(CLASS_NAME,RETURN,NAME,ARGS...) \
	typedef RETURN (* OOOPaste(OOOVirtual_,CLASS_NAME,_,NAME))(void * OOOThis); \
	static RETURN OOOPaste(CLASS_NAME,_,NAME)(CLASS_NAME * OOOThis) \
	OOOClassImplement2MethodBody(OOOPost(ARGS))
#define __OOOClassImplement2Method(CLASS_NAME,RETURN,NAME,ARGS...) OOOPaste(OOOClassImplement2Method,OOOIsEmpty(OOOPre(ARGS)))(CLASS_NAME,RETURN,NAME,ARGS)
#define _OOOClassImplement2Method(CLASS_NAME,ARGS...) __OOOClassImplement2Method(CLASS_NAME,ARGS)
#define OOOClassImplement2Method(FIRST,LAST,ITERATION,CLOSURE_LIST_REMAINDER...) \
	_OOOClassImplement2Method(OOOPreList(0,CLOSURE_LIST_REMAINDER),OOOPreList(1,CLOSURE_LIST_REMAINDER)) \
	OOOPostList(1,CLOSURE_LIST_REMAINDER)

#define OOOClassImplement2(NAME,ARGS...) \
	typedef struct \
	{ \
		OOOPaste(NAME,_VTable) * pVTable; \
		OOOPaste(NAME,_Interfaces) tInterfaces; \
		OOOForEach(OOOClassImplement2PrivateData,OOOPre(OOOFilter(OOOPrivateData2Label,ARGS))) \
	} \
	OOOPaste(NAME, _PrivateData); \
	OOOForEachClosure(OOOClassImplement2MethodDeclare,OOOList(NAME),OOOFilter(OOOMethod2Label,ARGS)) \
	typedef void (* OOOPaste(OOOVirtual_,NAME,_destroy))(void * OOOThis); \
	static void OOOPaste(NAME,_destroy)(NAME * OOOThis) GCCO_SAFE_DS; \
	static void OOOPaste(NAME,_destroy)(NAME * OOOThis) \
	{ \
		assert(OOOThis); \
		{ \
			OOOPre(OOOFilter(OOODestructor2Label,ARGS)) \
		} \
		O_free((OOOPaste(NAME,_PrivateData) *) OOOThis); \
	} \
	OOOForEachClosure(OOOClassImplement2Method,OOOList(NAME),OOOFilter(OOOMethod2Label,ARGS)) \

	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(ARGS)
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(void)
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) O_calloc(1, sizeof(OOOPaste(CLASS_NAME, _PrivateData))); \
		assert(OOOThis);
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(ARGS) GCCO_SAFE_DS; \
	OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct); \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(void) GCCO_SAFE_DS; \
	OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct); \
		{ \
			static OOOPaste(CLASS_NAME, _VTable) OOOVTable = \
			{ \
				OOOPaste(CLASS_NAME, _destroy)
				, OOOPaste(CLASS_NAME, _, METHOD_NAME)
			}; \
			OOOThis->pVTable = &OOOVTable; \
		}
		{ \
			static OOOPaste(INTERFACE_NAME, _VTable) OOOVTable = \
			{ \
				(OOOPaste(OOOVirtual_, CLASS_NAME, _destroy)) OOOPaste(CLASS_NAME, _destroy)
				, (OOOPaste(OOOVirtual_, CLASS_NAME, _, METHOD_NAME)) OOOPaste(CLASS_NAME, _, METHOD_NAME)
			}; \
			OOOThis->tInterfaces.OOOPaste(t, INTERFACE_NAME).pInstance = OOOThis; \
			OOOThis->tInterfaces.OOOPaste(t, INTERFACE_NAME).pVTable = &OOOVTable; \
		}
		return OOOThis; \
	}


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
