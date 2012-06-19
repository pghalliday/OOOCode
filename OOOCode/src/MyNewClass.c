#include "MyNewClass.h"
#include "OOOCode.h"

OOOC_Class(MyNewClass)
	int nMyField;
	char * szString;
	OOOC_Implement(AnotherInterface);
	OOOC_Implement(MyNewInterface);
END_CLASS

OOOC_ImplementCast(MyNewClass, AnotherInterface)
OOOC_ImplementCast(MyNewClass, MyNewInterface)

OOOC_Implementation(MyNewClass, char *, MyNewClass_anotherMethod, char * szFormat, int nArgument)
{
	if (SELF->szString)
	{
		O_free(SELF->szString);
	}
	SELF->szString = O_dsprintf(szFormat, nArgument, SELF->nMyField);
	return SELF->szString;
}
OOOC_EndImplementation

OOOC_Implementation(MyNewClass, int, MyNewClass_myMethod, int nArgument)
{
	return SELF->nMyField + nArgument;
}
OOOC_EndImplementation

OOOC_Constructor(MyNewClass, int nMyField)
{
	OOOC_ConstructInterface(AnotherInterface);
	OOOC_RegisterMethod(AnotherInterface, anotherMethod, MyNewClass_anotherMethod);
	OOOC_ConstructInterface(MyNewInterface);
	OOOC_RegisterMethod(MyNewInterface, myMethod, MyNewClass_myMethod);
	SELF->nMyField = nMyField;
}
OOOC_EndConstructor

OOOC_Destructor(MyNewClass)
{
	OOOC_DestroyInterface(AnotherInterface);
	OOOC_DestroyInterface(MyNewInterface);
	if (SELF->szString)
	{
		O_free(SELF->szString);
	}
}
OOOC_EndDestructor


