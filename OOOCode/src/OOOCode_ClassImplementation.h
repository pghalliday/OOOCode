#ifndef OOOCode_ClassImplementation_H
#define OOOCode_ClassImplementation_H

#include "opentv.h"

#define __OOOClass(CLASS_NAME) struct _##CLASS_NAME
#define _OOOClass(CLASS_NAME) __OOOClass(CLASS_NAME)
#define OOOClass _OOOClass(OOOClassName)
#define OOOImplement(INTERFACE_NAME)	INTERFACE_NAME t##INTERFACE_NAME

#define __OOOConstructor(CLASS_NAME, ARGS...) \
	CLASS_NAME * CLASS_NAME##_construct(ARGS) \
	{ \
		CLASS_NAME * OOOThis = O_calloc(1, sizeof(CLASS_NAME));
#define _OOOConstructor(CLASS_NAME, ARGS...) __OOOConstructor(CLASS_NAME, ##ARGS)
#define OOOConstructor(ARGS...) _OOOConstructor(OOOClassName, ##ARGS)
#define OOOConstructorEnd \
		return OOOThis; \
	}

#define __OOODestructor(CLASS_NAME) \
void CLASS_NAME##_destroy(CLASS_NAME * OOOThis) \
	{
#define _OOODestructor(CLASS_NAME) __OOODestructor(CLASS_NAME)
#define OOODestructor _OOODestructor(OOOClassName)
#define OOODestructorEnd \
		O_free(OOOThis); \
	}

#define __OOOImplementation(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE METHOD_NAME(void * INSTANCE, ##ARGS) \
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) INSTANCE;
#define _OOOImplementation(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) __OOOImplementation(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ##ARGS)
#define OOOImplementation(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOImplementation(OOOClassName, RETURN_TYPE, METHOD_NAME, ##ARGS)
#define OOOImplementationEnd \
	}

#define __OOOCastImplementation(CLASS_NAME, INTERFACE_NAME) \
	INTERFACE_NAME * CLASS_NAME##_as##INTERFACE_NAME(CLASS_NAME * OOOThis) \
	{ \
		INTERFACE_NAME * OOOThisInterface = &(OOOThis->t##INTERFACE_NAME); \
		OOOThisInterface->pInstance = OOOThis;
#define _OOOCastImplementation(CLASS_NAME, INTERFACE_NAME) __OOOCastImplementation(CLASS_NAME, INTERFACE_NAME)
#define OOOCastImplementation(INTERFACE_NAME) _OOOCastImplementation(OOOClassName, INTERFACE_NAME)
#define _OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME) \
		OOOThisInterface->METHOD_NAME = IMPLEMENTATION_METHOD_NAME
#define OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME) _OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME)
#define OOOCastImplementationEnd \
		return OOOThisInterface; \
	}

#endif
