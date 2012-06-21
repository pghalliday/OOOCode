#include "MyClass.h"

#include "OOOCode.h"
#define OOOClassName MyClass

OOOPrivateData
	int nMyField;
	char * szString;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOField(szString))
	{
		O_free(OOOField(szString));
	}
}
OOODestructorEnd

OOOImplementMethod(int, getMyField)
{
	return OOOField(nMyField);
}
OOOImplementMethodEnd

OOOImplementMethod(void, setMyField, int nMyField)
{
	OOOField(nMyField) = nMyField;
}
OOOImplementMethodEnd

OOOImplementVirtual(char *, IMyClass, anotherMethod, char * szFormat, int nArgument)
{
	if (OOOField(szString))
	{
		O_free(OOOField(szString));
	}
	OOOField(szString) = O_dsprintf(szFormat, nArgument, OOOField(nMyField));
	return OOOField(szString);
}
OOOImplementVirtualEnd

OOOImplementVirtual(int, IMyInterface, myMethod, int nArgument)
{
	return OOOField(nMyField) + nArgument;
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

	OOOField(nMyField) = nMyField;
}
OOOConstructorEnd

#undef OOOClassName
