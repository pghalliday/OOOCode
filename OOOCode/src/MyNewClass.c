#include "MyNewClass.h"

BEGIN_CLASS(MyNewClass)
ADD_FIELD(int nMyField)
ADD_FIELD(char * szString)
ADD_INTERFACE(AnotherInterface)
ADD_INTERFACE(MyNewInterface)
END_CLASS

IMPLEMENT_INTERFACE(MyNewClass, AnotherInterface)
IMPLEMENT_INTERFACE(MyNewClass, MyNewInterface)

BEGIN_INTERFACE_METHOD(MyNewClass, AnotherInterface, char *, anotherMethod, char * szFormat, int nArgument)
{
	if (SELF->szString)
	{
		O_free(SELF->szString);
	}
	SELF->szString = O_dsprintf(szFormat, nArgument, SELF->nMyField);
	return SELF->szString;
}
END_INTERFACE_METHOD

BEGIN_INTERFACE_METHOD(MyNewClass, MyNewInterface, int, myMethod, int nArgument)
{
	return SELF->nMyField + nArgument;
}
END_INTERFACE_METHOD

BEGIN_CONSTRUCTOR(MyNewClass, int nMyField)
{
	CONSTRUCT_INTERFACE(AnotherInterface);
	REGISTER_INTERFACE_METHOD(AnotherInterface, anotherMethod);
	CONSTRUCT_INTERFACE(MyNewInterface);
	REGISTER_INTERFACE_METHOD(MyNewInterface, myMethod);
	SELF->nMyField = nMyField;
}
END_CONSTRUCTOR

BEGIN_DESTRUCTOR(MyNewClass)
{
	DESTROY_INTERFACE(AnotherInterface);
	DESTROY_INTERFACE(MyNewInterface);
	if (SELF->szString)
	{
		O_free(SELF->szString);
	}
}
END_DESTRUCTOR


