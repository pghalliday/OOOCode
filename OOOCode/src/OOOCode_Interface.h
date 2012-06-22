#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

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
	{
#define _OOOVirtuals(INTERFACE_NAME) __OOOVirtuals(INTERFACE_NAME)
#define OOOVirtuals _OOOVirtuals(OOOInterface)

/* Declare a vtable entry */
#define _OOOVirtual(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * OOOInstance , ##ARGS)
#define OOOVirtual(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOVirtual(RETURN_TYPE, METHOD_NAME , ##ARGS)

/* end the vtable structure */
#define OOOVirtualsEnd \
	};

#endif
