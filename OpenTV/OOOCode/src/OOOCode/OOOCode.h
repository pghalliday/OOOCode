#ifndef OOOCode_H
#define OOOCode_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPastingAndQuoting.h"
#include "OOOEmptyArguments.h"
#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

/* Construct an instance of a class */
#define _OOOConstruct(CLASS_NAME, ARGS...) \
	CLASS_NAME##_construct(ARGS)
#define OOOConstruct(CLASS_NAME, ARGS...) _OOOConstruct(CLASS_NAME, ARGS)

/* destroy an instance of a class */
#define _OOODestroy(INSTANCE) \
	((INSTANCE)->pVTable->destroy(INSTANCE))
#define OOODestroy(INSTANCE) _OOODestroy(INSTANCE)

/* destroy an instance of a class through an interface */
#define _OOOIDestroy(INTERFACE) \
	((INTERFACE)->pVTable->destroy((INTERFACE)->pInstance))
#define OOOIDestroy(INTERFACE) _OOODestroy(INTERFACE)

/* cast an instance to an interface */
#define _OOOCast(INTERFACE_NAME, INSTANCE) \
	(&((INSTANCE)->tInterfaces.t##INTERFACE_NAME))
#define OOOCast(INTERFACE_NAME, INSTANCE) _OOOCast(INTERFACE_NAME, INSTANCE)

/* call an instance method through it's vtable */
#define _OOOCall0(INSTANCE, METHOD_NAME, ARGS...) \
	((INSTANCE)->pVTable->METHOD_NAME(INSTANCE, ARGS))
#define _OOOCall1(INSTANCE, METHOD_NAME, ARGS...) \
	((INSTANCE)->pVTable->METHOD_NAME(INSTANCE))
#define _OOOCall(INSTANCE, METHOD_NAME, ARGS...) OOOPaste(_OOOCall, OOOIsEmpty(ARGS))(INSTANCE, METHOD_NAME, ARGS)
#define OOOCall(INSTANCE, METHOD_NAME, ARGS...) _OOOCall(INSTANCE, METHOD_NAME, ARGS)

/* call an interface method through it's vtable */
#define _OOOICall0(INTERFACE, METHOD_NAME, ARGS...) \
	((INTERFACE)->pVTable->METHOD_NAME((INTERFACE)->pInstance, ARGS))
#define _OOOICall1(INTERFACE, METHOD_NAME, ARGS...) \
	((INTERFACE)->pVTable->METHOD_NAME((INTERFACE)->pInstance))
#define _OOOICall(INTERFACE, METHOD_NAME, ARGS...) OOOPaste(_OOOICall, OOOIsEmpty(ARGS))(INTERFACE, METHOD_NAME, ARGS)
#define OOOICall(INTERFACE, METHOD_NAME, ARGS...) _OOOICall(INTERFACE, METHOD_NAME, ARGS)

/* call an instance method directly (can only be used inside the class implementation) */
#define _OOOPCall0(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) \
	(CLASS_NAME##_##METHOD_NAME(INSTANCE, ARGS))
#define _OOOPCall1(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) \
	(CLASS_NAME##_##METHOD_NAME(INSTANCE))
#define _OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) OOOPaste(_OOOPCall, OOOIsEmpty(ARGS))(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS)
#define OOOPCall(INSTANCE, METHOD_NAME, ARGS...) _OOOPCall(OOOClass, INSTANCE, METHOD_NAME, ARGS)

/* access a field of the given instance */
#define __OOOField(CLASS_NAME, INSTANCE, FIELD_NAME) \
	(((CLASS_NAME##_PrivateData *) (INSTANCE))->FIELD_NAME)
#define _OOOField(CLASS_NAME, INSTANCE, FIELD_NAME) __OOOField(CLASS_NAME, INSTANCE, FIELD_NAME)
#define OOOField(INSTANCE, FIELD_NAME) _OOOField(OOOClass, INSTANCE, FIELD_NAME)

/* shortcut to access a field of the current OOOThis instance */
#define OOOF(FIELD_NAME) OOOField(OOOThis, FIELD_NAME)

/* shortcut to call an instance method directly with the current OOOThis instance */
#define OOOC(METHOD_NAME, ARGS...) OOOPCall(OOOThis, METHOD_NAME , ##ARGS)

#endif
