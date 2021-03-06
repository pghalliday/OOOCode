#ifndef OOOCode_ClassImplementation_H
#define OOOCode_ClassImplementation_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPaste.h"
#include "OOOIsEmpty.h"

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
#define _OOOPrivateData(CLASS_NAME) \
	typedef struct \
	{ \
		OOOPaste(CLASS_NAME, _VTable) * pVTable; \
		OOOPaste(CLASS_NAME, _Interfaces) tInterfaces;
#define OOOPrivateData _OOOPrivateData(OOOClass)

/* End the private data structure */
#define _OOOPrivateDataEnd(CLASS_NAME) \
	} \
	OOOPaste(CLASS_NAME, _PrivateData);
#define OOOPrivateDataEnd _OOOPrivateDataEnd(OOOClass)

/*
 * Destructor
 */

/* begin the destructor */
#define _OOODestructor(CLASS_NAME) \
	typedef void (* OOOPaste(OOOVirtual_, CLASS_NAME, _destroy))(void * OOOThis); \
	static void OOOPaste(CLASS_NAME, _destroy)(CLASS_NAME * OOOThis) GCCO_SAFE_DS; \
	static void OOOPaste(CLASS_NAME, _destroy)(CLASS_NAME * OOOThis) \
	{ \
		assert(OOOThis);
#define OOODestructor _OOODestructor(OOOClass)

/* end the destructor, freeing memory */
#define _OOODestructorEnd(CLASS_NAME) \
		O_free((OOOPaste(CLASS_NAME, _PrivateData) *) OOOThis); \
	}
#define OOODestructorEnd _OOODestructorEnd(OOOClass)

/*
 * Method
 */

/*
 * begin the method also creating a new type that is consistent with
 * the method prototype and can be used for safe casts when mapping
 * to virtuals in interface vtables
 */
#define OOOMethodVirtualType0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	typedef RETURN_TYPE (* OOOPaste(OOOVirtual_, CLASS_NAME, _, METHOD_NAME))(void * OOOThis, ARGS);
#define OOOMethodVirtualType1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	typedef RETURN_TYPE (* OOOPaste(OOOVirtual_, CLASS_NAME, _, METHOD_NAME))(void * OOOThis);
#define OOOMethodDeclaration0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis, ARGS) GCCO_SAFE_DS;
#define OOOMethodDeclaration1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis) GCCO_SAFE_DS;
#define OOOMethodSignature0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis, ARGS)
#define OOOMethodSignature1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	static RETURN_TYPE OOOPaste(CLASS_NAME, _, METHOD_NAME)(CLASS_NAME * OOOThis)
#define OOOMethodBody \
	{ \
		assert(OOOThis);
#define OOOMethod0OOOUndeclared(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	OOOMethodVirtualType0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS) \
	OOOMethodDeclaration0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS) \
	OOOMethodSignature0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS) \
	OOOMethodBody
#define OOOMethod1OOOUndeclared(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	OOOMethodVirtualType1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	OOOMethodDeclaration1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	OOOMethodSignature1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	OOOMethodBody
#define OOOMethod0OOODeclared(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	OOOMethodVirtualType0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS) \
	OOOMethodSignature0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS) \
	OOOMethodBody
#define OOOMethod1OOODeclared(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	OOOMethodVirtualType1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	OOOMethodSignature1(CLASS_NAME, RETURN_TYPE, METHOD_NAME) \
	OOOMethodBody
#define __OOOMethod(DECLARED, CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(OOOMethod, OOOIsEmpty(ARGS), DECLARED)(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define _OOOMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) __OOOMethod(OOOUndeclared, CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOMethod(OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOMethodDeclared(RETURN_TYPE, METHOD_NAME, ARGS...) __OOOMethod(OOODeclared, OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)

/* end the method */
#define OOOMethodEnd \
	}

/*
 * Constructor. Note that this actually allocates a private data
 * structure as described above but then casts it to the class type.
 * This may not seem very safe but it is wrapped in the macros which
 * have been tested and should not be a problem
 */

/* begin the constructor, allocating memory and set the exported construct method to the internal method */
#define OOOConstructorSignature0(CLASS_NAME, ARGS...) \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(ARGS)
#define OOOConstructorSignature1(CLASS_NAME) \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(void)
#define OOOConstructorBody(CLASS_NAME) \
	{ \
		CLASS_NAME * OOOThis = (CLASS_NAME *) O_calloc(1, sizeof(OOOPaste(CLASS_NAME, _PrivateData))); \
		assert(OOOThis);
#define OOOConstructor0OOOPublic(CLASS_NAME , ARGS...) \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(ARGS) GCCO_SAFE_DS; \
	OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct); \
	OOOConstructorSignature0(CLASS_NAME, ARGS) \
	OOOConstructorBody(CLASS_NAME)
#define OOOConstructor1OOOPublic(CLASS_NAME , ARGS...) \
	static CLASS_NAME * OOOPaste(_, CLASS_NAME, _construct)(void) GCCO_SAFE_DS; \
	OOOPaste(CLASS_NAME, _constructor) OOOPaste(CLASS_NAME, _construct) = OOOPaste(_, CLASS_NAME, _construct); \
	OOOConstructorSignature1(CLASS_NAME) \
	OOOConstructorBody(CLASS_NAME)
#define OOOConstructor0OOOPrivate(CLASS_NAME , ARGS...) \
	OOOConstructorSignature0(CLASS_NAME, ARGS) \
	OOOConstructorBody(CLASS_NAME)
#define OOOConstructor1OOOPrivate(CLASS_NAME , ARGS...) \
	OOOConstructorSignature1(CLASS_NAME) \
	OOOConstructorBody(CLASS_NAME)
#define __OOOConstructor(SCOPE, CLASS_NAME, ARGS...) OOOPaste(OOOPaste(OOOConstructor, OOOIsEmpty(ARGS)), SCOPE)(CLASS_NAME, ARGS)
#define _OOOConstructor(CLASS_NAME, ARGS...) __OOOConstructor(OOOPublic, CLASS_NAME, ARGS)
#define OOOConstructor(ARGS...) _OOOConstructor(OOOClass, ARGS)
#define OOOConstructorPrivate(ARGS...) __OOOConstructor(OOOPrivate, OOOClass, ARGS)

/*
 * Start the map of public methods to vtable entries. This is static
 * so that it is assigned at compile time and there is only one instance
 * in memory.
 */
#define _OOOMapMethods(CLASS_NAME) \
		{ \
			static OOOPaste(CLASS_NAME, _VTable) OOOVTable = \
			{ \
				OOOPaste(CLASS_NAME, _destroy)
#define OOOMapMethods _OOOMapMethods(OOOClass)

/* add methods to the vtable in the same order as they are declared in the class declaration */
#define _OOOMapMethod(CLASS_NAME, METHOD_NAME) \
				, OOOPaste(CLASS_NAME, _, METHOD_NAME)
#define OOOMapMethod(METHOD_NAME) _OOOMapMethod(OOOClass, METHOD_NAME)

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
			static OOOPaste(INTERFACE_NAME, _VTable) OOOVTable = \
			{ \
				(OOOPaste(OOOVirtual_, CLASS_NAME, _destroy)) OOOPaste(CLASS_NAME, _destroy)
#define _OOOMapVirtuals(INTERFACE_NAME) __OOOMapVirtuals(OOOClass, INTERFACE_NAME)
#define OOOMapVirtuals _OOOMapVirtuals(OOOInterface)

/* add methods to the vtable in the same order as they are declared in the interface declaration */
#define _OOOMapVirtual(CLASS_NAME, METHOD_NAME) \
				, (OOOPaste(OOOVirtual_, CLASS_NAME, _, METHOD_NAME)) OOOPaste(CLASS_NAME, _, METHOD_NAME)
#define OOOMapVirtual(METHOD_NAME) _OOOMapVirtual(OOOClass, METHOD_NAME)

/*
 * end the vtable mapping and assign to the instance
 *
 * #undef OOOInterface after calling this macro so that further interfaces
 * can be mapped
 */
#define _OOOMapVirtualsEnd(INTERFACE_NAME) \
			}; \
			OOOThis->tInterfaces.OOOPaste(t, INTERFACE_NAME).pInstance = OOOThis; \
			OOOThis->tInterfaces.OOOPaste(t, INTERFACE_NAME).pVTable = &OOOVTable; \
		}
#define OOOMapVirtualsEnd _OOOMapVirtualsEnd(OOOInterface)

/* end the constructor */
#define OOOConstructorEnd \
		return OOOThis; \
	}

#endif
