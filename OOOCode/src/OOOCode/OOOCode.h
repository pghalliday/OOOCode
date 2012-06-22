#ifndef OOOCode_H
#define OOOCode_H

/*
 * To use
 */


/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

/* Construct an instance of a class */
#define _OOOConstruct(CLASS_NAME, ARGS...) \
	CLASS_NAME##_construct(ARGS)
#define OOOConstruct(CLASS_NAME, ARGS...) _OOOConstruct(CLASS_NAME , ##ARGS)

/* destroy an instance of a class */
#define _OOODestroy(INSTANCE) \
	(INSTANCE->destroy(INSTANCE))
#define OOODestroy(INSTANCE) _OOODestroy(INSTANCE)

/* cast an instance to an interface */
#define _OOOCast(INTERFACE_NAME, INSTANCE) \
	(&(INSTANCE->tInterfaces.t##INTERFACE_NAME))
#define OOOCast(INTERFACE_NAME, INSTANCE) _OOOCast(INTERFACE_NAME, INSTANCE)

/* call an instance method through it's vtable */
#define _OOOCall(INSTANCE, METHOD_NAME, ARGS...) \
	(INSTANCE->pVTable->METHOD_NAME(INSTANCE , ##ARGS))
#define OOOCall(INSTANCE, METHOD_NAME, ARGS...) _OOOCall(INSTANCE, METHOD_NAME , ##ARGS)

/* call an interface method through it's vtable */
#define _OOOICall(INTERFACE, METHOD_NAME, ARGS...) \
	(INTERFACE->pVTable->METHOD_NAME(INTERFACE->pInstance , ##ARGS))
#define OOOICall(INTERFACE, METHOD_NAME, ARGS...) _OOOICall(INTERFACE, METHOD_NAME , ##ARGS)

/* call an instance method directly (can only be used inside the class implementation) */
#define __OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) \
	(CLASS_NAME##_##METHOD_NAME(INSTANCE , ##ARGS))
#define _OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) __OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME , ##ARGS)
#define OOOPCall(INSTANCE, METHOD_NAME, ARGS...) _OOOPCall(OOOClass, INSTANCE, METHOD_NAME , ##ARGS)

/* access a field of the given instance */
#define _OOOField(INSTANCE, FIELD_NAME) \
	(INSTANCE->pPrivateData->FIELD_NAME)
#define OOOField(INSTANCE, FIELD_NAME) _OOOField(INSTANCE, FIELD_NAME)

/* shortcut to access a field of the current OOOThis instance */
#define _OOOF(FIELD_NAME) \
	(OOOThis->pPrivateData->FIELD_NAME)
#define OOOF(FIELD_NAME) _OOOF(FIELD_NAME)

/* shortcut to call an instance method directly with the current OOOThis instance */
#define __OOOC(CLASS_NAME, METHOD_NAME, ARGS...) \
	(CLASS_NAME##_##METHOD_NAME(OOOThis , ##ARGS))
#define _OOOC(CLASS_NAME, METHOD_NAME, ARGS...) __OOOC(CLASS_NAME, METHOD_NAME , ##ARGS)
#define OOOC(METHOD_NAME, ARGS...) _OOOC(OOOClass, METHOD_NAME , ##ARGS)

#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

#endif
