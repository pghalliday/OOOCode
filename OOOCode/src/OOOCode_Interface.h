#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#define __OOOInterface(INTERFACE_NAME) \
	typedef struct _##INTERFACE_NAME##_VTable INTERFACE_NAME##_VTable; \
	typedef struct _##INTERFACE_NAME INTERFACE_NAME; \
	struct _##INTERFACE_NAME \
	{ \
		void * pInstance; \
		INTERFACE_NAME##_VTable * pVTable; \
	}; \
	struct _##INTERFACE_NAME##_VTable \
	{
#define _OOOInterface(INTERFACE_NAME) __OOOInterface(INTERFACE_NAME)
#define OOOInterface _OOOInterface(OOOInterfaceName)
#define __OOOVirtual(RETURN_TYPE, INTERFACE_NAME, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(INTERFACE_NAME * OOOIThis , ##ARGS)
#define _OOOVirtual(RETURN_TYPE, INTERFACE_NAME, METHOD_NAME, ARGS...) __OOOVirtual(RETURN_TYPE, INTERFACE_NAME, METHOD_NAME , ##ARGS)
#define OOOVirtual(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOVirtual(RETURN_TYPE, OOOInterfaceName, METHOD_NAME , ##ARGS)
#define OOOInterfaceEnd \
	};

#endif
