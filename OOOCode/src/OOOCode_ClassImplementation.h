#ifndef OOOCode_ClassImplementation_H
#define OOOCode_ClassImplementation_H

#include "opentv.h"

#define OOOC_Class(CLASS_NAME) \
	struct _##CLASS_NAME \
	{
#define OOOC_Implement(INTERFACE_NAME)	INTERFACE_NAME * p##INTERFACE_NAME;
#define END_CLASS \
	};

#define OOOC_ImplementCast(CLASS_NAME, INTERFACE_NAME) \
	INTERFACE_NAME * CLASS_NAME##_as##INTERFACE_NAME(CLASS_NAME * SELF) \
	{ \
		return SELF->p##INTERFACE_NAME; \
	}

#define OOOC_Implementation(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE METHOD_NAME(void * INSTANCE, ##ARGS) \
	{ \
		CLASS_NAME * SELF = (CLASS_NAME *) INSTANCE;
#define OOOC_EndImplementation \
	}

#define OOOC_Constructor(CLASS_NAME, ARGS...) \
	CLASS_NAME * CLASS_NAME##_construct(ARGS) \
	{ \
		CLASS_NAME * SELF = O_calloc(1, sizeof(CLASS_NAME));
#define OOOC_ConstructInterface(INTERFACE_NAME)	\
	SELF->p##INTERFACE_NAME = O_calloc(1, sizeof(INTERFACE_NAME)); \
	SELF->p##INTERFACE_NAME->pInstance = SELF
#define OOOC_RegisterMethod(INTERFACE_NAME, METHOD_NAME, IMPLEMENTATION_METHOD_NAME) SELF->p##INTERFACE_NAME->METHOD_NAME = IMPLEMENTATION_METHOD_NAME
#define OOOC_EndConstructor \
		return SELF; \
	}

#define OOOC_Destructor(CLASS_NAME) \
void CLASS_NAME##_destroy(CLASS_NAME * SELF) \
	{
#define OOOC_DestroyInterface(INTERFACE_NAME)	O_free(SELF->p##INTERFACE_NAME)
#define OOOC_EndDestructor \
		O_free(SELF); \
	}

#endif
