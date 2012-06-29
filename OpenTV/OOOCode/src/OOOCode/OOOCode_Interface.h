#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPastingAndQuoting.h"
#include "OOOEmptyArguments.h"

/*
 * Export virtual methods
 */

/* Declare the interface structure and start the vtable */
#define __OOOVirtuals(INTERFACE_NAME) \
	typedef struct _##INTERFACE_NAME##_VTable INTERFACE_NAME##_VTable; \
	typedef struct _##INTERFACE_NAME INTERFACE_NAME; \
	struct _##INTERFACE_NAME \
	{ \
		void * pInstance; \
		INTERFACE_NAME##_VTable * pVTable; \
	}; \
	struct _##INTERFACE_NAME##_VTable \
	{ \
		void (* destroy)(void * OOOThis);
#define _OOOVirtuals(INTERFACE_NAME) __OOOVirtuals(INTERFACE_NAME)
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
