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

#define __OOOPrivateData(CLASS_NAME) \
	struct _##CLASS_NAME##_PrivateData \
	{
#define _OOOPrivateData(CLASS_NAME) __OOOPrivateData(CLASS_NAME)
#define OOOPrivateData _OOOPrivateData(OOOClassName)
#define OOOPrivateDataEnd \
	};

#define __OOODestructor(CLASS_NAME) \
void CLASS_NAME##_destroy(CLASS_NAME * OOOThis) \
	{ \
		assert(OOOThis);
#define _OOODestructor(CLASS_NAME) __OOODestructor(CLASS_NAME)
#define OOODestructor _OOODestructor(OOOClassName)
#define OOODestructorEnd \
		O_free(OOOThis->pPrivateData); \
		O_free(OOOThis); \
	}

#define __OOOImplementMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE CLASS_NAME##_##METHOD_NAME(void * OOOInstance , ##ARGS) \
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) OOOInstance; \
		assert(OOOThis);
#define _OOOImplementMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) __OOOImplementMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOImplementMethod(OOOClassName, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOMethodEnd \
	}

#define __OOOConstructor(CLASS_NAME , ARGS...) \
	CLASS_NAME * CLASS_NAME##_construct(ARGS) \
	{ \
		CLASS_NAME * OOOThis = O_calloc(1, sizeof(CLASS_NAME)); \
		assert(OOOThis); \
		OOOThis->pPrivateData = O_calloc(1, sizeof(CLASS_NAME##_PrivateData)); \
		assert(OOOThis->pPrivateData); \
		OOOThis->destroy = CLASS_NAME##_destroy;
#define _OOOConstructor(CLASS_NAME, ARGS...) __OOOConstructor(CLASS_NAME , ##ARGS)
#define OOOConstructor(ARGS...) _OOOConstructor(OOOClassName , ##ARGS)
#define __OOOMapMethods(CLASS_NAME) \
		{ \
			static CLASS_NAME##_VTable OOOVTable = \
			{
#define _OOOMapMethods(CLASS_NAME) __OOOMapMethods(CLASS_NAME)
#define OOOMapMethods _OOOMapMethods(OOOClassName)
#define __OOOMethodMapping(CLASS_NAME, METHOD_NAME) \
				CLASS_NAME##_##METHOD_NAME
#define _OOOMethodMapping(CLASS_NAME, METHOD_NAME) __OOOMethodMapping(CLASS_NAME, METHOD_NAME)
#define OOOMethodMapping(METHOD_NAME) _OOOMethodMapping(OOOClassName, METHOD_NAME)
#define OOOMapMethodsEnd \
			}; \
			OOOThis->pVTable = &OOOVTable; \
		}
#define __OOOMapVirtuals(INTERFACE_NAME) \
		{ \
			static INTERFACE_NAME##_VTable OOOVTable = \
			{
#define _OOOMapVirtuals(INTERFACE_NAME) __OOOMapVirtuals(INTERFACE_NAME)
#define OOOMapVirtuals _OOOMapVirtuals(OOOInterfaceName)
#define __OOOVirtualMapping(CLASS_NAME, INTERFACE_NAME, METHOD_NAME) \
				CLASS_NAME##_##METHOD_NAME
#define _OOOVirtualMapping(CLASS_NAME, INTERFACE_NAME, METHOD_NAME) __OOOVirtualMapping(CLASS_NAME, INTERFACE_NAME, METHOD_NAME)
#define OOOVirtualMapping(METHOD_NAME) _OOOVirtualMapping(OOOClassName, OOOInterfaceName, METHOD_NAME)
#define __OOOMapVirtualsEnd(INTERFACE_NAME) \
			}; \
			OOOThis->tInterfaces.t##INTERFACE_NAME.pInstance = OOOThis; \
			OOOThis->tInterfaces.t##INTERFACE_NAME.pVTable = &OOOVTable; \
		}
#define _OOOMapVirtualsEnd(INTERFACE_NAME) __OOOMapVirtualsEnd(INTERFACE_NAME)
#define OOOMapVirtualsEnd _OOOMapVirtualsEnd(OOOInterfaceName)
#define OOOConstructorEnd \
		return OOOThis; \
	}

#endif
