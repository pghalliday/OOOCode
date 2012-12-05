#ifdef OOOClass
#ifdef OOOClosure
#ifdef OOOClosureType
#ifdef OOOClosureInterface
#ifdef OOOClosureInputs
#ifdef OOOClosureOutputs

#include "OOOCode.h"
#include "OOOForEach.h"
#include "OOOPaste.h"

#ifndef OOOCode_Closure_H
#define OOOCode_Closure_H

#define OOOClosureArgListComma0 ,
#define OOOClosureArgListComma1

#define OOOClosureOutputTypedArg(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	, VALUE OOOPaste(output, ITERATION) REMAINDER
#define OOOClosureOutputTypedArgs OOOForEach(OOOClosureOutputTypedArg, 1, OOOClosureOutputs)

#define OOOClosureInputTypedArg(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	, VALUE OOOPaste(input, ITERATION) REMAINDER
#define OOOClosureInputTypedArgs OOOForEach(OOOClosureInputTypedArg, 1, OOOClosureInputs)

#define OOOClosureOutputArg(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	, OOOPaste(output, ITERATION) REMAINDER
#define OOOClosureOutputArgs OOOForEach(OOOClosureOutputArg, 1, OOOClosureOutputs)

#define OOOClosurePrivateField(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	VALUE OOOPaste(input, ITERATION); \
	REMAINDER

#define OOOClosureAccessor(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	_OOOMethod(OOOClosure, VALUE, OOOPaste(accessor, ITERATION)) \
	{ \
		return _OOOField(OOOClosure, OOOThis, OOOPaste(input, ITERATION)); \
	} \
	OOOMethodEnd \
	\
	REMAINDER

#define OOOClosureAccessorMap(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	_OOOMapVirtual(OOOClosure, OOOPaste(accessor, ITERATION)) \
	REMAINDER

#define OOOClosureMapField(FIRST, LAST, ITERATION, VALUE, REMAINDER) \
	_OOOField(OOOClosure, OOOThis, OOOPaste(input, ITERATION)) = OOOPaste(input, ITERATION); \
	REMAINDER

#endif

typedef void (* OOOPaste(OOOClosure, _CallbackType))(OOOClass, OOOClosureType OOOClosureOutputTypedArgs)

__OOODeclare(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOPaste(OOOClosure, _CallbackType) cbCallback, OOOClosureType closureData OOOClosureInputTypedArgs)
	OOOImplements
		OOOImplement(OOOClosureInterface)
	_OOOImplementsEnd(OOOClosure)
	_OOOExports(OOOClosure)
	_OOOExportsEnd(OOOClosure)
_OOODeclareEnd(OOOClosure)

_OOOPrivateData(OOOClosure)
	OOOClass * pContainer;
	OOOPaste(OOOClosure, _CallbackType) cbCallback;
	OOOClosureType closureData;
	OOOForEach(OOOClosurePrivateField, 1, OOOClosureInputs)
_OOOPrivateDataEnd(OOOClosure)

_OOODestructor(OOOClosure)
_OOODestructorEnd(OOOClosure)

OOOForEach(OOOClosureAccessor, 1, OOOClosureInputs)

_OOOMethod(OOOClosure, void, callback OOOClosureOutputTypedArgs)
{
	_OOOField(OOOClosure, OOOThis, cbCallback)
	(
		_OOOField(OOOClosure, OOOThis, pContainer),
		_OOOField(OOOClosure, OOOThis, closureData) OOOClosureOutputArgs
	);
	OOODestroy(OOOThis);
}
OOOMethodEnd

__OOOConstructor(OOOPrivate, OOOClosure, OOOClass * pContainer, OOOPaste(OOOClosure, _CallbackType) cbCallback, OOOClosureType closureData OOOClosureInputTypedArgs)
{
	__OOOMapVirtuals(OOOClosure, OOOClosureInterface)
		OOOForEach(OOOClosureAccessorMap, 1, OOOClosureInputs)
		_OOOMapVirtual(OOOClosure, callback)
	_OOOMapVirtualsEnd(OOOClosureInterface)
	_OOOMapMethods(OOOClosure)
	OOOMapMethodsEnd

	OOOForEach(OOOClosureMapField, 1, OOOClosureInputs)
}
OOOConstructorEnd

#endif
#endif
#endif
#endif
#endif
#endif
