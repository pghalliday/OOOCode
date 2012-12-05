#ifdef OOOClass
#ifdef OOOClosure
#ifdef OOOClosureType
#ifdef OOOClosureInterface
#ifdef OOOClosureInputs
#ifdef OOOClosureOutputs

#include "OOOCode.h"
#include "OOOForEach.h"
#include "OOOSimplePaste.h"

#define OOOClosureArgSeparator0 ,
#define OOOClosureArgSeparator1

#define OOOClosureTypedArg(FIRST, LAST, ITERATION, TYPE, REMAINDER) \
	OOOSimplePaste(OOOClosureArgSeparator, FIRST) TYPE OOOSimplePaste(arg, ITERATION) REMAINDER
#define OOOClosureTypedArgs(TYPES...) OOOForEach(OOOClosureTypedArg, TYPES)

#define OOOClosureArg(FIRST, LAST, ITERATION, TYPE, REMAINDER) \
	OOOSimplePaste(OOOClosureArgSeparator, FIRST)  OOOSimplePaste(arg, ITERATION) REMAINDER
#define OOOClosureArgs(TYPES...) OOOForEach(OOOClosureArg, TYPES)

#define OOOClosurePrivateField(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	VALUE OOOSimplePaste(input, ITERATION); \
	REMAINDER

#define OOOClosureAccessor(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	_OOOMethod(OOOClosure, VALUE, OOOSimplePaste(accessor, ITERATION)) \
	{ \
		return _OOOField(OOOClosure, OOOThis, OOOSimplePaste(input, ITERATION)); \
	} \
	OOOMethodEnd \
	\
	REMAINDER

#define OOOClosureAccessorMap(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	_OOOMapVirtual(OOOClosure, OOOSimplePaste(accessor, ITERATION)) \
	REMAINDER

#define OOOClosureMapField(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	_OOOField(OOOClosure, OOOThis, OOOSimplePaste(input, ITERATION)) = OOOSimplePaste(arg, ITERATION); \
	REMAINDER

#define OOOClosureCallbackTypedef0(OUTPUT_TYPES...) \
	typedef void (* OOOSimplePaste(OOOClosure,_CallbackType))(OOOClass * pContainer, OOOClosureType closureData, OOOClosureTypedArgs(OUTPUT_TYPES));
#define OOOClosureCallbackTypedef1(OUTPUT_TYPES...) \
	typedef void (* OOOSimplePaste(OOOClosure,_CallbackType))(OOOClass * pContainer, OOOClosureType closureData);
#define OOOClosureCallbackTypedef(OUTPUT_TYPES...) OOOSimplePaste(OOOClosureCallbackTypedef,OOOIsEmpty(OUTPUT_TYPES))(OUTPUT_TYPES)

#define OOOClosureDeclare0(INPUT_TYPES...) \
	__OOODeclare(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOSimplePaste(OOOClosure,_CallbackType) cbCallback, OOOClosureType closureData, OOOClosureTypedArgs(INPUT_TYPES))
#define OOOClosureDeclare1(INPUT_TYPES...) \
	__OOODeclare(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOSimplePaste(OOOClosure,_CallbackType) cbCallback, OOOClosureType closureData)
#define OOOClosureDeclare(INPUT_TYPES...) OOOSimplePaste(OOOClosureDeclare,OOOIsEmpty(INPUT_TYPES))(INPUT_TYPES)

#define OOOClosureCallbackMethod0(OUTPUT_TYPES...) \
	_OOOMethod(OOOClosure, void, callback, OOOClosureTypedArgs(OUTPUT_TYPES))
#define OOOClosureCallbackMethod1(OUTPUT_TYPES...) \
	_OOOMethod(OOOClosure, void, callback)
#define OOOClosureCallbackMethod(OUTPUT_TYPES...) OOOSimplePaste(OOOClosureCallbackMethod,OOOIsEmpty(OUTPUT_TYPES))(OUTPUT_TYPES)

#define OOOClosureCallback0(OUTPUT_TYPES...) \
	_OOOField(OOOClosure, OOOThis, cbCallback) \
	( \
		_OOOField(OOOClosure, OOOThis, pContainer), \
		_OOOField(OOOClosure, OOOThis, closureData), \
		OOOClosureArgs(OUTPUT_TYPES) \
	);
#define OOOClosureCallback1(OUTPUT_TYPES...) \
	_OOOField(OOOClosure, OOOThis, cbCallback) \
	( \
		_OOOField(OOOClosure, OOOThis, pContainer), \
		_OOOField(OOOClosure, OOOThis, closureData) \
	);
#define OOOClosureCallback(OUTPUT_TYPES...) OOOSimplePaste(OOOClosureCallback,OOOIsEmpty(OUTPUT_TYPES))(OUTPUT_TYPES)

#define OOOClosureConstructor0(INPUT_TYPES...) \
	__OOOConstructor(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOSimplePaste(OOOClosure, _CallbackType) cbCallback, OOOClosureType closureData, OOOClosureTypedArgs(INPUT_TYPES))
#define OOOClosureConstructor1(INPUT_TYPES...) \
	__OOOConstructor(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOSimplePaste(OOOClosure, _CallbackType) cbCallback, OOOClosureType closureData)
#define OOOClosureConstructor(INPUT_TYPES...) OOOSimplePaste(OOOClosureConstructor,OOOIsEmpty(INPUT_TYPES))(INPUT_TYPES)

OOOClosureCallbackTypedef(OOOClosureOutputs)

OOOClosureDeclare(OOOClosureInputs)
	OOOImplements
		OOOImplement(OOOClosureInterface)
	_OOOImplementsEnd(OOOClosure)
	_OOOExports(OOOClosure)
	_OOOExportsEnd(OOOClosure)
_OOODeclareEnd(OOOClosure)

_OOOPrivateData(OOOClosure)
	OOOClass * pContainer;
	OOOSimplePaste(OOOClosure, _CallbackType) cbCallback;
	OOOClosureType closureData;
	OOOForEach(OOOClosurePrivateField, OOOClosureInputs)
_OOOPrivateDataEnd(OOOClosure)

_OOODestructor(OOOClosure)
_OOODestructorEnd(OOOClosure)

OOOForEach(OOOClosureAccessor, OOOClosureInputs)

OOOClosureCallbackMethod(OOOClosureOutputs)
{
	OOOClosureCallback(OOOClosureOutputs)
	OOODestroy(OOOThis);
}
OOOMethodEnd

OOOClosureConstructor(OOOClosureInputs)
{
	__OOOMapVirtuals(OOOClosure, OOOClosureInterface)
		OOOForEach(OOOClosureAccessorMap, OOOClosureInputs)
		_OOOMapVirtual(OOOClosure, callback)
	_OOOMapVirtualsEnd(OOOClosureInterface)
	_OOOMapMethods(OOOClosure)
	OOOMapMethodsEnd

	_OOOField(OOOClosure, OOOThis, pContainer) = pContainer;
	_OOOField(OOOClosure, OOOThis, cbCallback) = cbCallback;
	_OOOField(OOOClosure, OOOThis, closureData) = closureData;

	OOOForEach(OOOClosureMapField, OOOClosureInputs)
}
OOOConstructorEnd

#endif
#endif
#endif
#endif
#endif
#endif
