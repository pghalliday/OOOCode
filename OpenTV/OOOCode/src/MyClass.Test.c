#include "OOOUnitTestDefines.h"
#include "MyClass.h"

OOOTest(MyClass)
{
	MyClass * pMyClass = OOOConstruct(MyClass, 5);
	MyClass * pMyClassCopy = OOOCall(pMyClass, copy);

	/* Check stuff here */
	OOOCheck(OOOCall(pMyClass, getMyField) == 5);
	OOOCheck(OOOICall(OOOCast(IMyClass, pMyClass), getData) == 5);
	OOOCheck(OOOCall(pMyClassCopy, isEqual, pMyClass));
	OOOCheck(OOOCall(pMyClassCopy, getMyField) == 5);
	OOOCheck(pMyClassCopy != pMyClass);

	OOODestroy(pMyClass);
	OOODestroy(pMyClassCopy);
}
