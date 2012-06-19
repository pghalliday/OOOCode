#include "MyNewClass.h"
#include "OOOCode.h"

OOOClass(MyNewClass)
{
	int nMyField;
	char * szString;
	OOOImplement(AnotherInterface);
	OOOImplement(MyNewInterface);
};

OOOConstructor(MyNewClass, int nMyField)
{
	OOOThis->nMyField = nMyField;
}
OOOEndConstructor

OOODestructor(MyNewClass)
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
}
OOOEndDestructor

OOOImplementation(MyNewClass, char *, MyNewClass_anotherMethod, char * szFormat, int nArgument)
{
	if (OOOThis->szString)
	{
		O_free(OOOThis->szString);
	}
	OOOThis->szString = O_dsprintf(szFormat, nArgument, OOOThis->nMyField);
	return OOOThis->szString;
}
OOOEndImplementation

OOOImplementation(MyNewClass, int, MyNewClass_myMethod, int nArgument)
{
	return OOOThis->nMyField + nArgument;
}
OOOEndImplementation

OOOCastImplementation(MyNewClass, AnotherInterface)
{
	OOORegisterMethod(anotherMethod, MyNewClass_anotherMethod);
}
OOOEndCastImplementation

OOOCastImplementation(MyNewClass, MyNewInterface)
{
	OOORegisterMethod(myMethod, MyNewClass_myMethod);
}
OOOEndCastImplementation
