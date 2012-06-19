#ifndef OOOCode_H
#define OOOCode_H

/* Calling conventions */
#define _OOOConstruct(CLASS_NAME, ARGS...) \
	CLASS_NAME##_construct(ARGS)
#define OOOConstruct(CLASS_NAME, ARGS...) _OOOConstruct(CLASS_NAME, ##ARGS)

#define _OOODestroy(CLASS_NAME, INSTANCE) \
	CLASS_NAME##_destroy(INSTANCE)
#define OOODestroy(CLASS_NAME, INSTANCE) _OOODestroy(CLASS_NAME, INSTANCE)

#define _OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE) \
	CLASS_NAME##_as##INTERFACE_NAME(INSTANCE)
#define OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE) _OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE)

#define _OOOCall(INTERFACE, METHOD, ARGS...)	\
	(INTERFACE->METHOD(INTERFACE->pInstance, ##ARGS))
#define OOOCall(INTERFACE, METHOD, ARGS...) _OOOCall(INTERFACE, METHOD, ##ARGS)

#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

#endif
