#include "MyClass.h"

#define OOOClassName	MyClass
#include "OOOCode.h"

OOOClass
{
	int nMyField;
	char * szString;
	OOOImplement(AnotherInterface);
	OOOImplement(MyInterface);
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

OOOImplementation(char *, MyClass_anotherMethod, char * szFormat, int nArgument)
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
	OOOThis->szString = O_dsprintf(szFormat, nArgument, OOOThis->nMyField);
	return OOOThis->szString;
}
OOOImplementationEnd

OOOCastImplementation(AnotherInterface)
{
	OOORegisterMethod(anotherMethod, MyClass_anotherMethod);
}
OOOCastImplementationEnd

OOOImplementation(int, MyClass_myMethod, int nArgument)
{
	return OOOThis->nMyField + nArgument;
}
OOOImplementationEnd

OOOCastImplementation(MyInterface)
{
	OOORegisterMethod(myMethod, MyClass_myMethod);
}
OOOCastImplementationEnd
