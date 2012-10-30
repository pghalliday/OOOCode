#ifndef OOOCode_ClassImplementation_H
#define OOOCode_ClassImplementation_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPastingAndQuoting.h"
#include "OOOEmptyArguments.h"

#include "opentv.h"
#include "assert.h"

/*
 * Private data structure. This is the same as the main class
 * type structure except that it adds the private data fields.
 * When constructing an instance it is this structure that is
 * allocated. Internally casts are used to access fields and in
 * the destructor to ensure the correct memory is freed. We do
 * this to optimise the memory usage and access times for fields.
 */

/* begin the private data structure */
#define __OOOPrivateData(CLASS_NAME) \
	typedef struct \
	{ \
		CLASS_NAME##_VTable * pVTable; \
		CLASS_NAME##_Interfaces tInterfaces;
#define _OOOPrivateData(CLASS_NAME) __OOOPrivateData(CLASS_NAME)
#define OOOPrivateData _OOOPrivateData(OOOClass)

/* End the private data structure */
#define __OOOPrivateDataEnd(CLASS_NAME) \
	} \
	CLASS_NAME##_PrivateData;
#define _OOOPrivateDataEnd(CLASS_NAME) __OOOPrivateDataEnd(CLASS_NAME)
#define OOOPrivateDataEnd _OOOPrivateDataEnd(OOOClass)

/*
 * Destructor
 */

/* begin the destructor */
#define __OOODestructor(CLASS_NAME) \
	typedef void (* OOOVirtual_##CLASS_NAME##_destroy)(void * OOOThis); \
	static void CLASS_NAME##_destroy(CLASS_NAME * OOOThis) \
	{ \
		assert(OOOThis);
#define _OOODestructor(CLASS_NAME) __OOODestructor(CLASS_NAME)
#define OOODestructor _OOODestructor(OOOClass)

/* end the destructor, freeing memory */
#define __OOODestructorEnd(CLASS_NAME) \
		O_free((CLASS_NAME##_PrivateData *) OOOThis); \
	}
#define _OOODestructorEnd(CLASS_NAME) __OOODestructorEnd(CLASS_NAME)
#define OOODestructorEnd _OOODestructorEnd(OOOClass)

/*
 * Method
 */

/*
 * begin the method also creating a new type that is consistent with
 * the method prototype and can be used for safe casts when mapping
 * to virtuals in interface vtables
 */
#define _OOOMethod0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	typedef RETURN_TYPE (* OOOVirtual_##CLASS_NAME##_##METHOD_NAME)(void * OOOThis, ARGS); \
	static RETURN_TYPE CLASS_NAME##_##METHOD_NAME(CLASS_NAME * OOOThis, ARGS) \
	{ \
		assert(OOOThis);
#define _OOOMethod1(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	typedef RETURN_TYPE (* OOOVirtual_##CLASS_NAME##_##METHOD_NAME)(void * OOOThis); \
	static RETURN_TYPE CLASS_NAME##_##METHOD_NAME(CLASS_NAME * OOOThis) \
	{ \
		assert(OOOThis);
#define _OOOMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(_OOOMethod, OOOIsEmpty(ARGS))(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOMethod(OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)

/* end the method */
#define OOOMethodEnd \
	}

/*
 * Constructor. Note that this actually allocates a private data
 * structure as described above but then casts it to the class type.
 * This may not seem very safe but it is wrapped in the macros which
 * have been tested and should not be a problem
 */

/* begin the constructor, allocating memory */
#define __OOOConstructor(CLASS_NAME , ARGS...) \
	CLASS_NAME * CLASS_NAME##_construct(ARGS) \
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) O_calloc(1, sizeof(CLASS_NAME##_PrivateData)); \
		assert(OOOThis);
#define _OOOConstructor(CLASS_NAME, ARGS...) __OOOConstructor(CLASS_NAME, ARGS)
#define OOOConstructor(ARGS...) _OOOConstructor(OOOClass, ARGS)

/*
 * Start the map of public methods to vtable entries. This is static
 * so that it is assigned at compile time and there is only one instance
 * in memory.
 */
#define __OOOMapMethods(CLASS_NAME) \
		{ \
			static CLASS_NAME##_VTable OOOVTable = \
			{ \
				CLASS_NAME##_destroy
#define _OOOMapMethods(CLASS_NAME) __OOOMapMethods(CLASS_NAME)
#define OOOMapMethods _OOOMapMethods(OOOClass)

/* add methods to the vtable in the same order as they are declared in the class declaration */
#define __OOOMethodMapping(CLASS_NAME, METHOD_NAME) \
				, CLASS_NAME##_##METHOD_NAME
#define _OOOMethodMapping(CLASS_NAME, METHOD_NAME) __OOOMethodMapping(CLASS_NAME, METHOD_NAME)
#define OOOMethodMapping(METHOD_NAME) _OOOMethodMapping(OOOClass, METHOD_NAME)

/* end the vtable mapping and assign to the instance */
#define OOOMapMethodsEnd \
			}; \
			OOOThis->pVTable = &OOOVTable; \
		}

/*
 * Start a map of methods to interface vtable entries. This is static
 * so that it is assigned at compile time and there is only one instance
 * in memory.
 *
 * #define OOOInterface before calling this macro so that the compiler knows
 * which interface is being mapped
 *
 */
#define __OOOMapVirtuals(CLASS_NAME, INTERFACE_NAME) \
		{ \
			static INTERFACE_NAME##_VTable OOOVTable = \
			{ \
				(OOOVirtual_##CLASS_NAME##_destroy) CLASS_NAME##_destroy
#define _OOOMapVirtuals(CLASS_NAME, INTERFACE_NAME) __OOOMapVirtuals(CLASS_NAME, INTERFACE_NAME)
#define OOOMapVirtuals _OOOMapVirtuals(OOOClass, OOOInterface)

/* add methods to the vtable in the same order as they are declared in the interface declaration */
#define __OOOVirtualMapping(CLASS_NAME, METHOD_NAME) \
				, (OOOVirtual_##CLASS_NAME##_##METHOD_NAME) CLASS_NAME##_##METHOD_NAME
#define _OOOVirtualMapping(CLASS_NAME, METHOD_NAME) __OOOVirtualMapping(CLASS_NAME, METHOD_NAME)
#define OOOVirtualMapping(METHOD_NAME) _OOOVirtualMapping(OOOClass, METHOD_NAME)

/*
 * end the vtable mapping and assign to the instance
 *
 * #undef OOOInterface after calling this macro so that further interfaces
 * can be mapped
 */
#define __OOOMapVirtualsEnd(INTERFACE_NAME) \
			}; \
			OOOThis->tInterfaces.t##INTERFACE_NAME.pInstance = OOOThis; \
			OOOThis->tInterfaces.t##INTERFACE_NAME.pVTable = &OOOVTable; \
		}
#define _OOOMapVirtualsEnd(INTERFACE_NAME) __OOOMapVirtualsEnd(INTERFACE_NAME)
#define OOOMapVirtualsEnd _OOOMapVirtualsEnd(OOOInterface)

/* end the constructor */
#define OOOConstructorEnd \
		return OOOThis; \
	}

#endif
