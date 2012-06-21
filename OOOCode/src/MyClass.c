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

OOOPrivateMethod(int, printMyField)
{
	O_debug("MyField: %d\n", OOOField(OOOThis, nMyField));
	return OOOField(OOOThis, nMyField);
}
OOOPrivateMethodEnd

OOOImplementMethod(int, getMyField)
{
	return OOOPrivateCall(OOOThis, printMyField);
}
OOOImplementMethodEnd

OOOImplementMethod(void, setMyField, int nMyField)
{
	OOOField(OOOThis, nMyField) = nMyField;
}
OOOImplementMethodEnd

OOOImplementVirtual(char *, IMyClass, anotherMethod, char * szFormat, int nArgument)
{
	if (OOOField(OOOThis, szString))
	{
		O_free(OOOField(OOOThis, szString));
	}
	OOOField(OOOThis, szString) = O_dsprintf(szFormat, nArgument, OOOField(OOOThis, nMyField));
	return OOOField(OOOThis, szString);
}
OOOImplementVirtualEnd

OOOImplementVirtual(int, IMyInterface, myMethod, int nArgument)
{
	return OOOField(OOOThis, nMyField) + nArgument;
}
OOOImplementVirtualEnd

OOOConstructor(int nMyField)
{
	OOOMapMethods
		OOOMethodMapping(getMyField),
		OOOMethodMapping(setMyField)
	OOOMapMethodsEnd

	OOOMapVirtuals(IMyClass)
		OOOVirtualMapping(IMyClass, anotherMethod)
	OOOMapVirtualsEnd(IMyClass)

	OOOMapVirtuals(IMyInterface)
		OOOVirtualMapping(IMyInterface, myMethod)
	OOOMapVirtualsEnd(IMyInterface)

	OOOField(OOOThis, nMyField) = nMyField;
}
OOOConstructorEnd

#undef OOOClassName
