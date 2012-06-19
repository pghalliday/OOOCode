#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

#define OOOC_Interface \
	typedef struct \
	{ \
		void * pInstance;
#define OOOC_Method(METHOD_NAME, ARGS...)	(* METHOD_NAME)(void * pInstance, ##ARGS)
#define OOOC_EndInterface(INTERFACE_NAME) \
	} \
	INTERFACE_NAME; \

#endif
