#ifndef OOOCode_Header2_H
#define OOOCode_Header2_H

#include "OOOPaste.h"
#include "OOOFilter.h"
#include "OOOPre.h"
#include "OOOPost.h"
#include "OOOPreList.h"
#include "OOOPostList.h"
#include "OOOForEachList.h"
#include "OOOForEachClosure.h"
#include "OOOIsEmpty.h"

#define OOOConstructor2Label	1
#define OOOImplement2Label		2
#define OOOExport2Label			3

#define OOOConstructor2(ARGS...)	OOOList(OOOConstructor2Label,ARGS)
#define OOOImplement2(ARG)	OOOList(OOOImplement2Label,ARG)
#define OOOExport2(ARGS...)	OOOList(OOOExport2Label,ARGS)

#define OOOClassDeclare2ConstructorType0(NAME,ARGS...) \
	typedef NAME * (* OOOPaste(NAME,_constructor))(ARGS);
#define OOOClassDeclare2ConstructorType1(NAME,ARGS...) \
	typedef NAME * (* OOOPaste(NAME,_constructor))(void);
#define OOOClassDeclare2ConstructorType(NAME,ARGS...) OOOPaste(OOOClassDeclare2ConstructorType,OOOIsEmpty(ARGS))(NAME,ARGS)

#define _OOOClassDeclare2Implement(NAME) \
	NAME OOOPaste(t,NAME);
#define OOOClassDeclare2Implement(FIRST,LAST,ITERATION,NAME_AND_REMAINDER...) \
	_OOOClassDeclare2Implement(OOOPre(NAME_AND_REMAINDER)) \
	OOOPost(NAME_AND_REMAINDER)

#define OOOClassDeclare2Export0(CLASS_NAME,RETURN,NAME,ARGS...) \
		RETURN (* NAME)(CLASS_NAME * OOOThis, ARGS);
#define OOOClassDeclare2Export1(CLASS_NAME,RETURN,NAME,ARGS...) \
		RETURN (* NAME)(CLASS_NAME * OOOThis);
#define __OOOClassDeclare2Export(CLASS_NAME,RETURN,NAME,ARGS...) OOOPaste(OOOClassDeclare2Export,OOOIsEmpty(ARGS))(CLASS_NAME,RETURN,NAME,ARGS)
#define _OOOClassDeclare2Export(CLASS_NAME,ARGS...) __OOOClassDeclare2Export(CLASS_NAME,ARGS)
#define OOOClassDeclare2Export(FIRST,LAST,ITERATION,CLOSURE_AND_LIST_AND_REMAINDER...) \
	_OOOClassDeclare2Export(OOOPreList(0,CLOSURE_AND_LIST_AND_REMAINDER),OOOPreList(1,CLOSURE_AND_LIST_AND_REMAINDER)) \
	OOOPostList(1,CLOSURE_AND_LIST_AND_REMAINDER)

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
		OOOForEachList(OOOClassDeclare2Implement,OOOFilter(OOOImplement2Label,ARGS)) \
	} \
	OOOPaste(NAME,_Interfaces); \
	typedef struct \
	{ \
		void (* destroy)(NAME * OOOThis); \
		OOOForEachClosure(OOOClassDeclare2Export,OOOList(NAME),OOOFilter(OOOExport2Label,ARGS)) \
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

#endif
