#include "opentv.h"

/*
Prototype a method signature to be implemented for
this interface. Allows the compiler to spot errors
but can't get round the void pointer for the instance
*/
typedef int (* MyInterface_MyMethod)(void * pInstance, int nArgument);

/* Interface structure (vtable?) */
typedef struct
{
	void * pInstance;
	MyInterface_MyMethod cbMyMethod;
}
MyInterface;

/*
Interface constructor. I use static inline for all
interface methods so that they compile out much like
preprocessor stuff but also the compiler will help me
with type checking, etc
*/
static inline MyInterface * MyInterface_create(void * pInstance, MyInterface_MyMethod cbMyMethod)
{
	MyInterface * pThis = O_malloc(sizeof(MyInterface));
	pThis->pInstance = pInstance;
	pThis->cbMyMethod = cbMyMethod;
	return pThis;
}

/* Interface destructor */
static inline void MyInterface_destroy(MyInterface * pThis)
{
	O_free(pThis);
}

/*
This method allows the implementation of MyInterface_MyMethod
to be called thus facilitating polymorphism which is our end goal
*/
static inline int MyInterface_myMethod(MyInterface * pThis, int nArgument)
{
	return pThis->cbMyMethod(pThis->pInstance, nArgument);
}
