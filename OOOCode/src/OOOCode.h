#ifndef OOOCode_H
#define OOOCode_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#define _OOOConstruct(CLASS_NAME, ARGS...) \
	CLASS_NAME##_construct(ARGS)
#define OOOConstruct(CLASS_NAME, ARGS...) _OOOConstruct(CLASS_NAME , ##ARGS)

#define _OOODestroy(INSTANCE) \
	(INSTANCE->destroy(INSTANCE))
#define OOODestroy(INSTANCE) _OOODestroy(INSTANCE)

#define _OOOCast(INTERFACE_NAME, INSTANCE) \
	(&(INSTANCE->tInterfaces.t##INTERFACE_NAME))
#define OOOCast(INTERFACE_NAME, INSTANCE) _OOOCast(INTERFACE_NAME, INSTANCE)

#define _OOOCall(INSTANCE, METHOD_NAME, ARGS...) \
	(INSTANCE->pVTable->METHOD_NAME(INSTANCE , ##ARGS))
#define OOOCall(INSTANCE, METHOD_NAME, ARGS...) _OOOCall(INSTANCE, METHOD_NAME , ##ARGS)

#define _OOOICall(INTERFACE, METHOD_NAME, ARGS...) \
	(INTERFACE->pVTable->METHOD_NAME(INTERFACE->pInstance , ##ARGS))
#define OOOICall(INTERFACE, METHOD_NAME, ARGS...) _OOOICall(INTERFACE, METHOD_NAME , ##ARGS)

#define __OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) \
	(CLASS_NAME##_##METHOD_NAME(INSTANCE , ##ARGS))
#define _OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME, ARGS...) __OOOPCall(CLASS_NAME, INSTANCE, METHOD_NAME , ##ARGS)
#define OOOPCall(INSTANCE, METHOD_NAME, ARGS...) _OOOPCall(OOOClass, INSTANCE, METHOD_NAME , ##ARGS)

#define _OOOField(INSTANCE, FIELD_NAME) \
	(INSTANCE->pPrivateData->FIELD_NAME)
#define OOOField(INSTANCE, FIELD_NAME) _OOOField(INSTANCE, FIELD_NAME)

#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

#endif
