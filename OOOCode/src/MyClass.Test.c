#include "OOOUnitTestDefines.h"
#include "MyClass.h"

OOOTest(MyClass)
{
	MyClass * pMyClass = OOOConstruct(MyClass, 5);

	/* Check stuff here */
	OOOCheck(OOOCall(pMyClass, getMyField) == 5);
	OOOCheck(OOOICall(OOOCast(IMyClass, pMyClass), getData) == 5);

	OOODestroy(pMyClass);
}
