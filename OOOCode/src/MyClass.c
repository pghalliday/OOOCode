#include "MyClass.h"
#include "OOOCode.h"

OOOClass(MyClass)
{
	int nMyField;
	char * szString;
	OOOImplement(AnotherInterface);
	OOOImplement(MyInterface);
};

OOOConstructor(MyClass, int nMyField)
{
	OOOThis->nMyField = nMyField;
}
OOOConstructorEnd

OOODestructor(MyClass)
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
}
OOODestructorEnd

OOOImplementation(MyClass, char *, MyClass_anotherMethod, char * szFormat, int nArgument)
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
	OOOThis->szString = O_dsprintf(szFormat, nArgument, OOOThis->nMyField);
	return OOOThis->szString;
}
OOOImplementationEnd

OOOCastImplementation(MyClass, AnotherInterface)
{
	OOORegisterMethod(anotherMethod, MyClass_anotherMethod);
}
OOOCastImplementationEnd

OOOImplementation(MyClass, int, MyClass_myMethod, int nArgument)
{
	return OOOThis->nMyField + nArgument;
}
OOOImplementationEnd

OOOCastImplementation(MyClass, MyInterface)
{
	OOORegisterMethod(myMethod, MyClass_myMethod);
}
OOOCastImplementationEnd
