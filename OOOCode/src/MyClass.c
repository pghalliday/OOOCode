#include "MyClass.h"
#include "OOOCode.h"

#define OOOClassName MyClass

OOOClass
{
	int nMyField;
	char * szString;
	OOOImplement(IMyClass);
	OOOImplement(IMyInterface);
};

OOOConstructor(int nMyField)
{
	OOOThis->nMyField = nMyField;
}
OOOConstructorEnd

OOODestructor
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
}
OOODestructorEnd

OOOMethod(int, getMyField)
{
	return OOOThis->nMyField;
}
OOOMethodEnd

OOOMethod(void, setMyField, int nMyField)
{
	OOOThis->nMyField = nMyField;
}
OOOMethodEnd

OOOImplementMethod(char *, MyClass_anotherMethod, char * szFormat, int nArgument)
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
	OOOThis->szString = O_dsprintf(szFormat, nArgument, OOOThis->nMyField);
	return OOOThis->szString;
}
OOOImplementMethodEnd

OOOImplementCast(IMyClass)
{
	OOORegisterMethod(anotherMethod, MyClass_anotherMethod);
}
OOOImplementCastEnd

OOOImplementMethod(int, MyClass_myMethod, int nArgument)
{
	return OOOThis->nMyField + nArgument;
}
OOOImplementMethodEnd

OOOImplementCast(IMyInterface)
{
	OOORegisterMethod(myMethod, MyClass_myMethod);
}
OOOImplementCastEnd
