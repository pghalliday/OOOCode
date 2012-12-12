#ifndef OOOCode_Interface2_H
#define OOOCode_Interface2_H

#include "OOOList.h"
#include "OOOPaste.h"
#include "OOOForEachList.h"
#include "OOOIsEmpty.h"
#include "OOOPost.h"
#include "OOOPre.h"
#include "OOOFilter.h"

#define OOOVirtual2Label		0

#define OOOVirtual2(ARGS...)	OOOList(OOOVirtual2Label,ARGS)

#define OOOInterfaceVirtual20(RETURN,NAME,ARGS...) \
	RETURN (* NAME)(void * OOOInstance, ARGS);
#define OOOInterfaceVirtual21(RETURN,NAME,ARGS...) \
	RETURN (* NAME)(void * OOOInstance);
#define __OOOInterfaceVirtual2(RETURN,NAME,ARGS...) OOOPaste(OOOInterfaceVirtual2,OOOIsEmpty(ARGS))(RETURN,NAME,ARGS)
#define _OOOInterfaceVirtual2(ARGS...) __OOOInterfaceVirtual2(ARGS)
#define OOOInterfaceVirtual2(FIRST,LAST,ITERATION,LIST_REMAINDER...) \
	_OOOInterfaceVirtual2(OOOPre(LIST_REMAINDER)) \
	OOOPost(LIST_REMAINDER)

#define _OOOInterface2(NAME,LISTS...) \
	typedef struct OOOPaste(_,NAME,_VTable) OOOPaste(NAME,_VTable); \
	typedef struct OOOPaste(_,NAME) NAME; \
	struct OOOPaste(_,NAME) \
	{ \
		void * pInstance; \
		OOOPaste(NAME,_VTable) * pVTable; \
	}; \
	struct OOOPaste(_,NAME,_VTable) \
	{ \
		void (* idestroy)(void * OOOThis); \
		OOOForEachList(OOOInterfaceVirtual2,OOOFilter(OOOVirtual2Label,LISTS)) \
	};
#define OOOInterface2(ARGS...) _OOOInterface2(ARGS)

#endif
