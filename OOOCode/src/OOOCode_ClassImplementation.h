#ifndef OOOCode_ClassImplementation_H
#define OOOCode_ClassImplementation_H

#include "opentv.h"

#define OOOClass(CLASS_NAME) struct _##CLASS_NAME
#define OOOImplement(INTERFACE_NAME)	INTERFACE_NAME t##INTERFACE_NAME

#define OOOConstructor(CLASS_NAME, ARGS...) \
	CLASS_NAME * CLASS_NAME##_construct(ARGS) \
	{ \
		CLASS_NAME * OOOThis = O_calloc(1, sizeof(CLASS_NAME));
#define OOOConstructorEnd \
		return OOOThis; \
	}

#define OOODestructor(CLASS_NAME) \
void CLASS_NAME##_destroy(CLASS_NAME * OOOThis) \
	{
#define OOODestructorEnd \
		O_free(OOOThis); \
	}

#define OOOImplementation(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE METHOD_NAME(void * INSTANCE, ##ARGS) \
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) INSTANCE;
#define OOOImplementationEnd \
	}


#define OOOCastImplementation(CLASS_NAME, INTERFACE_NAME) \
	INTERFACE_NAME * CLASS_NAME##_as##INTERFACE_NAME(CLASS_NAME * OOOThis) \
	{ \
		INTERFACE_NAME * INTERFACE = &(OOOThis->t##INTERFACE_NAME); \
		INTERFACE->pInstance = OOOThis;
#define OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME) \
		INTERFACE->METHOD_NAME = IMPLEMENTATION_METHOD_NAME
#define OOOCastImplementationEnd \
		return INTERFACE; \
	}

#endif
