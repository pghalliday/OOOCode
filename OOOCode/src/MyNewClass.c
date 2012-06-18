#include "MyNewClass.h"

BEGIN_FIELDS(MyNewClass)
	ADD_FIELD(int nMyField)
END_FIELDS

IMPLEMENT_INTERFACE_METHOD(MyNewInterface, int, myMethod, int nArgument)
{
	return FIELD(MyNewClass, nMyField) + nArgument;
}

static MyNewInterface_VTable MyNewClass_tMyNewInterface_VTable =
{
	MyNewInterface_myMethod
};

static void MyNewClass_destroy(MyNewClass * pThis)
{
	O_free(pThis->pFields);
	MyNewInterface_destroy(pThis->pMyNewInterface);
	O_free(pThis);
}

MyNewClass * MyNewClass_construct(int nMyField)
{
	MyNewClass * pThis = O_malloc(sizeof(MyNewClass));
	pThis->destroy = MyNewClass_destroy;
	pThis->pMyNewInterface = MyNewInterface_construct(pThis, &MyNewClass_tMyNewInterface_VTable);
	pThis->pFields = O_malloc(sizeof(MyNewClass_Fields));
	pThis->pFields->nMyField = nMyField;
	return pThis;
}

