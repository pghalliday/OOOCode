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
#include "OOOForEachList.h"

#define OOOPrivateData2Label	4
#define OOOConstructor2Label	5
#define OOODestructor2Label		6
#define OOOMethod2Label			7

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

#define __OOOClassImplement2ConstructorImplementExport(CLASS_NAME,NAME,ARGS...) \
	, OOOPaste(CLASS_NAME,_,NAME)
#define _OOOClassImplement2ConstructorImplementExport(CLASS_NAME,ARGS...) __OOOClassImplement2ConstructorImplementExport(CLASS_NAME,ARGS)
#define OOOClassImplement2ConstructorImplementExport(FIRST,LAST,ITERATION,CLOSURE_LIST_REMAINDER...) \
	_OOOClassImplement2ConstructorImplementExport(OOOPreList(0,CLOSURE_LIST_REMAINDER),OOOPreList(1,CLOSURE_LIST_REMAINDER)) \
	OOOPostList(1,CLOSURE_LIST_REMAINDER)

#define OOOClassImplement2ConstructorImplementInterfaceMethod(FIRST,LAST,ITERATION,NAME,REMAINDER...) \
	, (OOOPaste(OOOVirtual_,CLASS_NAME,_,NAME)) OOOPaste(CLASS_NAME,_,NAME) \
	REMAINDER

#define __OOOClassImplement2ConstructorImplementInterface(CLASS_NAME,NAME,METHODS...) \
	static OOOPaste(NAME,_VTable) OOOPaste(OOO,NAME,VTable) = \
	{ \
		(OOOPaste(OOOVirtual_,CLASS_NAME,_destroy)) OOOPaste(CLASS_NAME,_destroy) \
		OOOForEach(OOOClassImplement2ConstructorImplementInterfaceMethod,METHODS) \
	};
#define _OOOClassImplement2ConstructorImplementInterface(CLASS_NAME,METHODS...) __OOOClassImplement2ConstructorImplementInterface(CLASS_NAME,METHODS)
#define OOOClassImplement2ConstructorImplementInterface(FIRST,LAST,ITERATION,CLOSURE_LIST_REMAINDER...) \
	_OOOClassImplement2ConstructorImplementInterface(OOOPreList(0,CLOSURE_LIST_REMAINDER),OOOPreList(1,CLOSURE_LIST_REMAINDER)) \
	OOOPostList(1,CLOSURE_LIST_REMAINDER)

#define __OOOClassImplement2ConstructorAssignInterface(NAME,METHODS...) \
	OOOThis->tInterfaces.OOOPaste(t,NAME).pInstance = OOOThis; \
	OOOThis->tInterfaces.OOOPaste(t,NAME).pVTable = &OOOPaste(OOO,NAME,VTable);
#define _OOOClassImplement2ConstructorAssignInterface(ARGS...) __OOOClassImplement2ConstructorAssignInterface(ARGS)
#define OOOClassImplement2ConstructorAssignInterface(FIRST,LAST,ITERATION,LIST_REMAINDER...) \
	_OOOClassImplement2ConstructorAssignInterface(OOOPre(LIST_REMAINDER)) \
	OOOPost(LIST_REMAINDER)

#define OOOClassImplement2ConstructorImplement(CLASS_NAME,ARGS) \
	{ \
		static OOOPaste(CLASS_NAME,_VTable) OOOVTable = \
		{ \
			OOOPaste(CLASS_NAME, _destroy) \
			OOOForEachClosure(OOOClassImplement2ConstructorImplementExport,OOOList(CLASS_NAME),OOOPreList(1,ARGS)) \
		}; \
		OOOForEachClosure(OOOClassImplement2ConstructorImplementInterface,OOOList(CLASS_NAME),OOOPreList(0,ARGS)) \
		CLASS_NAME * OOOThis = (CLASS_NAME *) O_calloc(1, sizeof(OOOPaste(CLASS_NAME,_PrivateData))); \
		assert(OOOThis); \
		OOOThis->pVTable = &OOOVTable; \
		OOOForEachList(OOOClassImplement2ConstructorAssignInterface,OOOList(CLASS_NAME),OOOPreList(0,ARGS)) \
		{ \
			OOOPost(OOOPostList(1,ARGS)) \
		} \
		return OOOThis; \
	} \
	OOOPaste(CLASS_NAME,_constructor) OOOPaste(CLASS_NAME,_construct) = OOOPaste(_,CLASS_NAME,_construct);
#define OOOClassImplement2Constructor0(CLASS_NAME,ARGS...) \
	static CLASS_NAME * OOOPaste(_,CLASS_NAME,_construct)(OOOPre(OOOPostList(1,ARGS))) GCCO_SAFE_DS; \
	static CLASS_NAME * OOOPaste(_,CLASS_NAME,_construct)(OOOPre(OOOPostList(1,ARGS))) \
	OOOClassImplement2ConstructorImplement(CLASS_NAME,ARGS)
#define OOOClassImplement2Constructor1(CLASS_NAME,ARGS...) \
	static CLASS_NAME * OOOPaste(_,CLASS_NAME,_construct)(void) GCCO_SAFE_DS; \
	static CLASS_NAME * OOOPaste(_,CLASS_NAME,_construct)(void) \
	OOOClassImplement2ConstructorImplement(CLASS_NAME,ARGS)
#define OOOClassImplement2Constructor(CLASS_NAME,ARGS...) OOOPaste(OOOClassImplement2Constructor,OOOIsEmpty(OOOPre(OOOPostList(1,ARGS))))(CLASS_NAME,ARGS)

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
	OOOClassImplement2Constructor(NAME,OOOList(OOOFilter(OOOImplement2Label,ARGS)),OOOList(OOOFilter(OOOExport2Label,ARGS)),OOOPre(OOOFilter(OOOConstructor2Label,ARGS)))

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
