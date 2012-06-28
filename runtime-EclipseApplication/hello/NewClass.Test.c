#include "OOOUnitTestDefines.h"
#include "NewClass.h"

OOOTest(NewClass)
{
	NewClass * pNewClass = OOOConstruct(NewClass);

	/* Check stuff here */
	OOOCheck(pNewClass);

	OOODestroy(pNewClass);
}
