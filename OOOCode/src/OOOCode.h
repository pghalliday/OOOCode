#ifndef OOOCODE_H_
#define OOOCODE_H_

#include "opentv.h"

/* Calling conventions */

#define CONSTRUCT(CLASS_NAME, ARGS...)		CLASS_NAME##_construct(##ARGS)
#define DESTROY(INSTANCE)					INSTANCE->destroy(INSTANCE)
#define INTERFACE(INTERFACE_NAME, INSTANCE)	(INSTANCE->p##INTERFACE_NAME)
#define CALL(INTERFACE, METHOD, ARGS...)	(INTERFACE->pVTable->METHOD(INTERFACE->pInstance, ##ARGS))

/* Class implementation stuff */

#define BEGIN_FIELDS(CLASS_NAME) \
	struct _##CLASS_NAME##_Fields \
	{
#define ADD_FIELD(FIELD)	FIELD;
#define END_FIELDS \
	};

#define IMPLEMENT_INTERFACE_METHOD(INTERFACE_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE INTERFACE_NAME##_##METHOD_NAME(void * pInstance, ##ARGS)
#define FIELD(CLASS_NAME, FIELD_NAME)	(((CLASS_NAME *) pInstance)->pFields->FIELD_NAME)


/* Class header stuff */

#define BEGIN_CLASS(CLASS_NAME, CONSTRUCTOR_ARGS...) \
	typedef struct _##CLASS_NAME CLASS_NAME; \
	extern CLASS_NAME * CLASS_NAME##_construct(##CONSTRUCTOR_ARGS); \
	typedef struct _##CLASS_NAME##_Fields CLASS_NAME##_Fields; \
	struct _##CLASS_NAME \
	{ \
		void (* destroy)(CLASS_NAME * pThis); \
		CLASS_NAME##_Fields * pFields;
#define ADD_INTERFACE(INTERFACE_NAME)	INTERFACE_NAME * p##INTERFACE_NAME;
#define END_CLASS \
	};

/* Interface header stuff */

#define BEGIN_INTERFACE \
	typedef struct \
	{
#define INTERFACE_METHOD(RETURN_TYPE, METHOD_NAME, ARGS...)	RETURN_TYPE (* METHOD_NAME)(void * pInstance, ##ARGS);
#define END_INTERFACE(INTERFACE_NAME) \
	} \
	INTERFACE_NAME##_VTable; \
	\
	typedef struct \
	{ \
		void * pInstance; \
		INTERFACE_NAME##_VTable * pVTable; \
	} \
	INTERFACE_NAME; \
	\
	static inline INTERFACE_NAME * INTERFACE_NAME##_construct(void * pInstance, INTERFACE_NAME##_VTable * pVTable) \
	{ \
		INTERFACE_NAME * pThis = O_malloc(sizeof(INTERFACE_NAME)); \
		pThis->pInstance = pInstance; \
		pThis->pVTable = pVTable; \
		return pThis; \
	} \
	\
	static inline void INTERFACE_NAME##_destroy(INTERFACE_NAME * pThis) \
	{ \
		O_free(pThis); \
	}


#endif
