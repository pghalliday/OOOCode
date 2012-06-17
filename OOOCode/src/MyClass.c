#include "MyClass.h"
#include "opentv.h"

struct _MyClass
{
	/* Need a field to store the interface instance */
	MyInterface * pMyInterface;
	int nMyField;
};

/*
private implementation of a MyInterface_MyMethod method - we keep
the void pointer parameter so that we don't have to cast the method
when passing it into the interface constructor. Doing so could hide nasty
type errors further down the road.
*/
static int MyClass_myMethod(void * pInstance, int nArgument)
{
	/*
	this #define is an optimisation that I use instead
	of adding a local variable to the stack. It's pretty
	optional but I worry about this sort of thing when
	running code on low horsepower set top boxes
	*/
	#define pThis	((MyClass *) pInstance)

	/* ooh, look - that's what myMethod is for ;) */
	return pThis->nMyField + nArgument;

	/*
	let's not forget to undef pThis we may want to use
	that name a lot in other methods ;)
	*/
	#undef pThis
}

MyClass * MyClass_create(int nMyField)
{
	MyClass * pThis = O_malloc(sizeof(MyClass));
	/* Construct an interface instance */
	pThis->pMyInterface = MyInterface_create(pThis, MyClass_myMethod);
	pThis->nMyField = nMyField;
	return pThis;
}

void MyClass_destroy(MyClass * pThis)
{
	/* don't forget to destroy the interface instance */
	MyInterface_destroy(pThis->pMyInterface);
	O_free(pThis);
}

int MyClass_getMyField(MyClass * pThis)
{
	return pThis->nMyField;
}

/* Casting convention implementation */
MyInterface * MyClass_asMyInterface(MyClass * pThis)
{
	return pThis->pMyInterface;
}
