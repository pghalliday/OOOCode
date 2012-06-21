#ifndef OOOCode_H
#define OOOCode_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#ifdef OOOClassName
#error "OOOClassName should not be defined before including OOOCode.h - check that previous includes have #undef'd it"
#endif

#ifdef OOOInterfaceName
#error "OOOInterfaceName should not be defined before including OOOCode.h - check that previous includes have #undef'd it"
#endif

#define _OOOConstruct(CLASS_NAME, ARGS...) \
	CLASS_NAME##_construct(ARGS)
#define OOOConstruct(CLASS_NAME, ARGS...) _OOOConstruct(CLASS_NAME , ##ARGS)

#define _OOODestroy(INSTANCE) \
	(INSTANCE->pVTable->destroy(INSTANCE))
#define OOODestroy(INSTANCE) _OOODestroy(INSTANCE)

#define _OOOCast(INTERFACE_NAME, INSTANCE) \
	(&(INSTANCE->tInterfaces.t##INTERFACE_NAME))
#define OOOCast(INTERFACE_NAME, INSTANCE) _OOOCast(INTERFACE_NAME, INSTANCE)

#define _OOOCall(INSTANCE, METHOD_NAME, ARGS...) \
	(INSTANCE->pVTable->METHOD_NAME(INSTANCE , ##ARGS))
#define OOOCall(INSTANCE, METHOD_NAME, ARGS...) _OOOCall(INSTANCE, METHOD_NAME , ##ARGS)

#define _OOOField(FIELD_NAME) \
	(OOOThis->pPrivateData->FIELD_NAME)
#define OOOField(FIELD_NAME) _OOOField(FIELD_NAME)

#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

#endif
