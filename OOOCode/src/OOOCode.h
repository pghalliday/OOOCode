#ifndef OOOCode_H
#define OOOCode_H

/* Calling conventions */

#define OOOConstruct(CLASS_NAME, ARGS...)				CLASS_NAME##_construct(ARGS)
#define OOODestroy(CLASS_NAME, INSTANCE)				CLASS_NAME##_destroy(INSTANCE)
#define OOOCast(CLASS_NAME, INTERFACE_NAME, INSTANCE)	CLASS_NAME##_as##INTERFACE_NAME(INSTANCE)
#define OOOCall(INTERFACE, METHOD, ARGS...)				(INTERFACE->METHOD(INTERFACE->pInstance, ##ARGS))

#include "OOOCode_Interface.h"
#include "OOOCode_ClassHeader.h"
#include "OOOCode_ClassImplementation.h"

#endif
