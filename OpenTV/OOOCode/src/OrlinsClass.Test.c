#include "OOOUnitTestDefines.h"
#include "OrlinsClass.h"

OOOTest(OrlinsClass)
{
	OrlinsClass * pOrlinsClass = OOOConstruct(OrlinsClass);

	/* Check stuff here */
	OOOCheck(pOrlinsClass != NULL);

	OOODestroy(pOrlinsClass);
}
