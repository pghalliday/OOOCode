#ifndef OOOCode_ClassImplementation_H
#define OOOCode_ClassImplementation_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "opentv.h"
#include "assert.h"

#define __OOOClass(CLASS_NAME) struct _##CLASS_NAME
#define _OOOClass(CLASS_NAME) __OOOClass(CLASS_NAME)
#define OOOClass _OOOClass(OOOClassName)
#define OOOImplement(INTERFACE_NAME)	INTERFACE_NAME t##INTERFACE_NAME

#define __OOOConstructor(CLASS_NAME, ARGS...) \
	CLASS_NAME * CLASS_NAME##_construct(ARGS) \
	{ \
		CLASS_NAME * OOOThis = O_calloc(1, sizeof(CLASS_NAME)); \
		assert(OOOThis);
#define _OOOConstructor(CLASS_NAME, ARGS...) __OOOConstructor(CLASS_NAME , ##ARGS)
#define OOOConstructor(ARGS...) _OOOConstructor(OOOClassName , ##ARGS)
#define OOOConstructorEnd \
		return OOOThis; \
	}

#define __OOODestructor(CLASS_NAME) \
void CLASS_NAME##_destroy(CLASS_NAME * OOOThis) \
	{ \
		assert(OOOThis);
#define _OOODestructor(CLASS_NAME) __OOODestructor(CLASS_NAME)
#define OOODestructor _OOODestructor(OOOClassName)
#define OOODestructorEnd \
		O_free(OOOThis); \
	}

#define __OOOMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE CLASS_NAME##_##METHOD_NAME(CLASS_NAME * OOOThis , ##ARGS) \
	{ \
		assert(OOOThis);
#define _OOOMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) __OOOMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOMethod(OOOClassName, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOMethodEnd \
	}

#define __OOOImplementMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE METHOD_NAME(void * INSTANCE , ##ARGS) \
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) INSTANCE; \
		assert(OOOThis);
#define _OOOImplementMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) __OOOImplementMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOImplementMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOImplementMethod(OOOClassName, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOImplementMethodEnd \
	}

#define __OOOImplementCast(CLASS_NAME, INTERFACE_NAME) \
	INTERFACE_NAME * CLASS_NAME##_as##INTERFACE_NAME(CLASS_NAME * OOOThis) \
	{ \
		assert(OOOThis); \
		{ \
			INTERFACE_NAME * OOOThisInterface = &(OOOThis->t##INTERFACE_NAME); \
			OOOThisInterface->pInstance = OOOThis;
#define _OOOImplementCast(CLASS_NAME, INTERFACE_NAME) __OOOImplementCast(CLASS_NAME, INTERFACE_NAME)
#define OOOImplementCast(INTERFACE_NAME) _OOOImplementCast(OOOClassName, INTERFACE_NAME)
#define _OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME) \
			OOOThisInterface->METHOD_NAME = IMPLEMENTATION_METHOD_NAME
#define OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME) _OOORegisterMethod(METHOD_NAME, IMPLEMENTATION_METHOD_NAME)
#define OOOImplementCastEnd \
			return OOOThisInterface; \
		} \
	}

#endif
