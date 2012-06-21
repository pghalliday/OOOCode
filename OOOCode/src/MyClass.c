#include "MyClass.h"

#include "OOOCode.h"
#define OOOClassName MyClass

OOOPrivateData
	int nMyField;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(int, printMyFieldX)
{
	O_debug("MyField: %d\n", OOOField(OOOThis, nMyField));
	return OOOField(OOOThis, nMyField);
}
OOOMethodEnd

OOOMethod(int, getMyFieldX)
{
	return OOOPrivateCall(OOOThis, printMyFieldX);
}
OOOMethodEnd

OOOMethod(void, setMyFieldX, int nMyField)
{
	OOOField(OOOThis, nMyField) = nMyField;
}
OOOMethodEnd

OOOMethod(int, myMethodX, int nArgument)
{
	return OOOField(OOOThis, nMyField) + nArgument;
}
OOOMethodEnd

OOOConstructor(int nMyField)
{
	OOOMapMethods
		OOOMethodMapping(getMyFieldX),
		OOOMethodMapping(setMyFieldX)
	OOOMapMethodsEnd

	#define OOOInterfaceName IMyInterface
	OOOMapVirtuals
		OOOVirtualMapping(myMethodX)
	OOOMapVirtualsEnd
	#undef OOOInterfaceName

	OOOField(OOOThis, nMyField) = nMyField;
}
OOOConstructorEnd

#undef OOOClassName
