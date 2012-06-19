#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#define _OOOInterface(INTERFACE_NAME) \
	typedef struct _##INTERFACE_NAME INTERFACE_NAME; \
	struct _##INTERFACE_NAME \
	{ \
		void * pInstance;
#define OOOInterface(INTERFACE_NAME) _OOOInterface(INTERFACE_NAME)
#define _OOOInterfaceMethod(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * pInstance , ##ARGS)
#define OOOInterfaceMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOInterfaceMethod(RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOInterfaceEnd \
	};

#endif
