#include "MyClass.h"

#include "OOOCode.h"
#define OOOClassName MyClass

OOOPrivateData
	int nMyField;
	char * szString;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOField(OOOThis, szString))
	{
		O_free(OOOField(OOOThis, szString));
	}
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

OOOMethod(char *, anotherMethodX, char * szFormat, int nArgument)
{
	if (OOOField(OOOThis, szString))
	{
		O_free(OOOField(OOOThis, szString));
	}
	OOOField(OOOThis, szString) = O_dsprintf(szFormat, nArgument, OOOField(OOOThis, nMyField));
	return OOOField(OOOThis, szString);
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

	#define OOOInterfaceName IMyClass
	OOOMapVirtuals
		OOOVirtualMapping(anotherMethodX)
	OOOMapVirtualsEnd
	#undef OOOInterfaceName

	#define OOOInterfaceName IMyInterface
	OOOMapVirtuals
		OOOVirtualMapping(myMethodX)
	OOOMapVirtualsEnd
	#undef OOOInterfaceName

	OOOField(OOOThis, nMyField) = nMyField;
}
OOOConstructorEnd

#undef OOOClassName
