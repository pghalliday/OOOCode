#ifndef OOOCode_H
#define OOOCode_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "assert.h"

#define _OOOConstruct(CLASS_NAME, ARGS...) \
	CLASS_NAME##_construct(ARGS)
#define OOOConstruct(CLASS_NAME, ARGS...) _OOOConstruct(CLASS_NAME , ##ARGS)

#define _OOODestroy(CLASS_NAME, INSTANCE) \
	CLASS_NAME##_destroy(INSTANCE)
#define OOODestroy(CLASS_NAME, INSTANCE) _OOODestroy(CLASS_NAME, INSTANCE)

#define _OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE) \
	CLASS_NAME##_as##INTERFACE_NAME(INSTANCE)
#define OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE) _OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE)

#define _OOOCall(INTERFACE, METHOD_NAME, ARGS...)	\
	(INTERFACE->METHOD_NAME(INTERFACE->pInstance , ##ARGS))
#define OOOCall(INTERFACE, METHOD_NAME, ARGS...) _OOOCall(INTERFACE, METHOD_NAME , ##ARGS)

#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

#endif
