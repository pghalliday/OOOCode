#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

#define OOOInterface(INTERFACE_NAME) \
	typedef struct _##INTERFACE_NAME INTERFACE_NAME; \
	struct _##INTERFACE_NAME \
	{ \
		void * pInstance;
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...)	RETURN_TYPE (* METHOD_NAME)(void * pInstance, ##ARGS)
#define OOOEndInterface \
	};

#endif
