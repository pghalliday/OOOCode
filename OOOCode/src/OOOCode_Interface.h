#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

#define _OOOInterface(INTERFACE_NAME) \
	typedef struct _##INTERFACE_NAME INTERFACE_NAME; \
	struct _##INTERFACE_NAME \
	{ \
		void * pInstance;
#define OOOInterface(INTERFACE_NAME) _OOOInterface(INTERFACE_NAME)
#define _OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * pInstance, ##ARGS)
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOMethod(RETURN_TYPE, METHOD_NAME, ##ARGS)
#define OOOInterfaceEnd \
	};

#endif
