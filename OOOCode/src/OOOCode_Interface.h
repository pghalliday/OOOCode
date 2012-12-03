#ifndef OOOCode_Interface_H
#define OOOCode_Interface_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPaste.h"
#include "OOOIsEmpty.h"

/*
 * Export virtual methods
 */

/* Declare the interface structure and start the vtable */
#define __OOOVirtuals(INTERFACE_NAME) \
	typedef struct _##INTERFACE_NAME##_VTable INTERFACE_NAME##_VTable; \
	typedef struct _##INTERFACE_NAME INTERFACE_NAME; \
	struct _##INTERFACE_NAME \
	{ \
		void * pInstance; \
		INTERFACE_NAME##_VTable * pVTable; \
	}; \
	struct _##INTERFACE_NAME##_VTable \
	{ \
		void (* idestroy)(void * OOOThis);
#define _OOOVirtuals(INTERFACE_NAME) __OOOVirtuals(INTERFACE_NAME)
#define OOOVirtuals _OOOVirtuals(OOOInterface)

/* Declare a vtable entry */
#define _OOOVirtual0(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * OOOInstance, ARGS);
#define _OOOVirtual1(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * OOOInstance);
#define OOOVirtual(RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(_OOOVirtual, OOOIsEmpty(ARGS))(RETURN_TYPE, METHOD_NAME, ARGS)

/* end the vtable structure */
#define OOOVirtualsEnd \
	};

/*
 * Closure definition macros
 */

#define __OOOClosureCallbackType(CLOSURE_NAME, CLASS_NAME, CLOSURE_TYPE, CALLBACK_ARG_TYPES...) \
	typedef void (* CLOSURE_NAME##_CALLBACK)(CLASS_NAME * pInstance, CLOSURE_TYPE * pClosure, CALLBACK_ARG_TYPES);
#define _OOOClosureCallbackType(CLOSURE_NAME, CLASS_NAME, CLOSURE_TYPE, CALLBACK_ARG_TYPES...) __OOOClosureCallbackType(CLOSURE_NAME, CLASS_NAME, CLOSURE_TYPE, CALLBACK_ARG_TYPES)
#define OOOClosureCallbackType(CLOSURE_TYPE, CALLBACK_ARG_TYPES...) _OOOClosureCallbackType(OOOClosure, OOOClass, CLOSURE_TYPE, CALLBACK_ARG_TYPES)

#define __OOOClosureImplementation(CLOSURE_NAME, INTERFACE_NAME, CLASS_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES...) \
	__OOODeclare(OOOPrivate, CLOSURE_NAME, CLASS_NAME * pInstance, CLOSURE_NAME##_CALLBACK cbCallback, CLOSURE_TYPE * pClosure, CONSTRUCT_ARG_TYPES) \
		OOOImplements \
			OOOImplement(INTERFACE_NAME) \
		_OOOImplementsEnd(CLOSURE_NAME) \
		_OOOExports(CLOSURE_NAME) \
		_OOOExportsEnd(CLOSURE_NAME) \
	_OOODeclareEnd(CLOSURE_NAME) \
	_OOOPrivateData(CLOSURE_NAME) \
		CLASS_NAME * pInstance; \
		CLOSURE_NAME##_CALLBACK cbCallback; \
		CLOSURE_TYPE * pClosure;
#define _OOOClosureImplementation(CLOSURE_NAME, INTERFACE_NAME, CLASS_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES...) __OOOClosureImplementation(CLOSURE_NAME, INTERFACE_NAME, CLASS_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES)
#define OOOClosureImplementation(INTERFACE_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES...) _OOOClosureImplementation(OOOClosure, INTERFACE_NAME, OOOClass, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES)

#define __OOOClosurePrivateDataEnd(CLOSURE_NAME) \
	_OOOPrivateDataEnd(CLOSURE_NAME) \
	_OOODestructor(CLOSURE_NAME) \
	_OOODestructorEnd(CLOSURE_NAME)
#define _OOOClosurePrivateDataEnd(CLOSURE_NAME) __OOOClosurePrivateDataEnd(CLOSURE_NAME)
#define OOOClosurePrivateDataEnd _OOOClosurePrivateDataEnd(OOOClosure)

#define __OOOClosureMapPrivateData(CLOSURE_NAME, TYPE, METHOD_NAME, FIELD_NAME) \
	_OOOMethod(CLOSURE_NAME, TYPE, METHOD_NAME) \
	{ \
		return _OOOField(CLOSURE_NAME, OOOThis, FIELD_NAME); \
	} \
	OOOMethodEnd
#define _OOOClosureMapPrivateData(CLOSURE_NAME, TYPE, METHOD_NAME, FIELD_NAME) __OOOClosureMapPrivateData(CLOSURE_NAME, TYPE, METHOD_NAME, FIELD_NAME)
#define OOOClosureMapPrivateData(TYPE, METHOD_NAME, FIELD_NAME) _OOOClosureMapPrivateData(OOOClosure, TYPE, METHOD_NAME, FIELD_NAME)

#define __OOOClosureCallbackStart(CLOSURE_NAME, METHOD_NAME, CALLBACK_ARG_TYPES...) \
	_OOOMethod(CLOSURE_NAME, void, METHOD_NAME, CALLBACK_ARG_TYPES) \
	{
#define _OOOClosureCallbackStart(CLOSURE_NAME, METHOD_NAME, CALLBACK_ARG_TYPES...) __OOOClosureCallbackStart(CLOSURE_NAME, METHOD_NAME, CALLBACK_ARG_TYPES)
#define OOOClosureCallbackStart(METHOD_NAME, CALLBACK_ARG_TYPES...) _OOOClosureCallbackStart(OOOClosure, METHOD_NAME, CALLBACK_ARG_TYPES)

#define __OOOClosureCallbackEnd(CLOSURE_NAME, CALLBACK_ARGS...) \
		_OOOField(CLOSURE_NAME, OOOThis, cbCallback)(_OOOField(CLOSURE_NAME, OOOThis, pInstance), _OOOField(CLOSURE_NAME, OOOThis, pClosure), CALLBACK_ARGS); \
		OOODestroy(OOOThis); \
	} \
	OOOMethodEnd
#define _OOOClosureCallbackEnd(CLOSURE_NAME, CALLBACK_ARGS...) __OOOClosureCallbackEnd(CLOSURE_NAME, CALLBACK_ARGS)
#define OOOClosureCallbackEnd(CALLBACK_ARGS...) _OOOClosureCallbackEnd(OOOClosure, CALLBACK_ARGS)

#define __OOOClosureConstructor(CLOSURE_NAME, INTERFACE_NAME, CLASS_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES...) \
	__OOOConstructor(OOOPrivate, CLOSURE_NAME, CLASS_NAME * pInstance, CLOSURE_NAME##_CALLBACK cbCallback, CLOSURE_TYPE * pClosure, CONSTRUCT_ARG_TYPES) \
	{ \
		__OOOMapVirtuals(CLOSURE_NAME, INTERFACE_NAME)
#define _OOOClosureConstructor(CLOSURE_NAME, INTERFACE_NAME, CLASS_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES...) __OOOClosureConstructor(CLOSURE_NAME, INTERFACE_NAME, CLASS_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES)
#define OOOClosureConstructor(INTERFACE_NAME, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES...) _OOOClosureConstructor(OOOClosure, INTERFACE_NAME, OOOClass, CLOSURE_TYPE, CONSTRUCT_ARG_TYPES)

#define __OOOClosureMapVirtual(CLOSURE_NAME, METHOD_NAME) \
			_OOOMapVirtual(CLOSURE_NAME, METHOD_NAME)
#define _OOOClosureMapVirtual(CLOSURE_NAME, METHOD_NAME) __OOOClosureMapVirtual(CLOSURE_NAME, METHOD_NAME)
#define OOOClosureMapVirtual(METHOD_NAME) _OOOClosureMapVirtual(OOOClosure, METHOD_NAME)

#define __OOOClosureMapFields(CLOSURE_NAME, INTERFACE_NAME) \
		_OOOMapVirtualsEnd(INTERFACE_NAME) \
		_OOOMapMethods(CLOSURE_NAME) \
		OOOMapMethodsEnd \
		_OOOField(CLOSURE_NAME, OOOThis, pInstance) = pInstance; \
		_OOOField(CLOSURE_NAME, OOOThis, cbCallback) = cbCallback; \
		_OOOField(CLOSURE_NAME, OOOThis, pClosure) = pClosure;
#define _OOOClosureMapFields(CLOSURE_NAME, INTERFACE_NAME) __OOOClosureMapFields(CLOSURE_NAME, INTERFACE_NAME)
#define OOOClosureMapFields(INTERFACE_NAME) _OOOClosureMapFields(OOOClosure, INTERFACE_NAME)

#define __OOOClosureMapField(CLOSURE_NAME, FIELD_NAME) \
		_OOOField(CLOSURE_NAME, OOOThis, FIELD_NAME) = FIELD_NAME;
#define _OOOClosureMapField(CLOSURE_NAME, FIELD_NAME) __OOOClosureMapField(CLOSURE_NAME, FIELD_NAME)
#define OOOClosureMapField(FIELD_NAME) _OOOClosureMapField(OOOClosure, FIELD_NAME)

#define OOOClosureMapFieldsEnd \
	} \
	OOOConstructorEnd

#endif
