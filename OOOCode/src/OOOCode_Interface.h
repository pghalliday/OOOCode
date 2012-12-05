#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPaste.h"
#include "OOOIsEmpty.h"

/*
 * Export virtual methods
 */

/* Declare the interface structure and start the vtable */
#define _OOOVirtuals(INTERFACE_NAME) \
	typedef struct OOOPaste(_, INTERFACE_NAME, _VTable) OOOPaste(INTERFACE_NAME, _VTable); \
	typedef struct OOOPaste(_, INTERFACE_NAME) INTERFACE_NAME; \
	struct OOOPaste(_, INTERFACE_NAME) \
	{ \
		void * pInstance; \
		OOOPaste(INTERFACE_NAME, _VTable) * pVTable; \
	}; \
	struct OOOPaste(_, INTERFACE_NAME, _VTable) \
	{ \
		void (* idestroy)(void * OOOThis);
#define OOOVirtuals _OOOVirtuals(OOOInterface)

/* Declare a vtable entry */
#define _OOOVirtual0(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * OOOInstance, ARGS);
#define _OOOVirtual1(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * OOOInstance);
#define OOOVirtual(RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(_OOOVirtual, OOOIsEmpty(ARGS))(RETURN_TYPE, METHOD_NAME, ARGS)

/* end the vtable structure */
#define OOOVirtualsEnd \
	};

#endif
