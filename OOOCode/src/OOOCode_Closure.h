#ifdef OOOClass
#ifdef OOOClosure
#ifdef OOOClosureType
#ifdef OOOClosureInterface
#ifdef OOOClosureInputs
#ifdef OOOClosureOutputs

#include "OOOCode.h"
#include "OOOForEach.h"
#include "OOOSimplePaste.h"

#ifndef OOOCode_Closure_H
#define OOOCode_Closure_H

#define OOOClosureArgSeparator0 ,
#define OOOClosureArgSeparator1

#define OOOClosureOutputTypedArg(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	OOOSimplePaste(OOOClosureArgSeparator, FIRST) VALUE OOOSimplePaste(output, ITERATION) REMAINDER
#define OOOClosureOutputTypedArgs OOOForEach(OOOClosureOutputTypedArg, OOOClosureOutputs)

#define OOOClosureInputTypedArg(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	OOOSimplePaste(OOOClosureArgSeparator, FIRST)  VALUE OOOSimplePaste(input, ITERATION) REMAINDER
#define OOOClosureInputTypedArgs OOOForEach(OOOClosureInputTypedArg, OOOClosureInputs)

#define OOOClosureOutputArg(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	OOOSimplePaste(OOOClosureArgSeparator, FIRST)  OOOSimplePaste(output, ITERATION) REMAINDER
#define OOOClosureOutputArgs OOOForEach(OOOClosureOutputArg, OOOClosureOutputs)

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
	_OOOField(OOOClosure, OOOThis, OOOSimplePaste(input, ITERATION)) = OOOSimplePaste(input, ITERATION); \
	REMAINDER

#endif

typedef void (* OOOSimplePaste(OOOClosure, _CallbackType))(OOOClass *, OOOClosureType, OOOClosureOutputTypedArgs);

__OOODeclare(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOSimplePaste(OOOClosure, _CallbackType) cbCallback, OOOClosureType closureData, OOOClosureInputTypedArgs)
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

_OOOMethod(OOOClosure, void, callback, OOOClosureOutputTypedArgs)
{
	_OOOField(OOOClosure, OOOThis, cbCallback)
	(
		_OOOField(OOOClosure, OOOThis, pContainer),
		_OOOField(OOOClosure, OOOThis, closureData),
		OOOClosureOutputArgs
	);
	OOODestroy(OOOThis);
}
OOOMethodEnd

__OOOConstructor(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOSimplePaste(OOOClosure, _CallbackType) cbCallback, OOOClosureType closureData, OOOClosureInputTypedArgs)
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
