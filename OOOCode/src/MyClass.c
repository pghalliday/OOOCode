#include "MyClass.h"

#define OOOClass MyClass

/* Declare any private data fields here */
OOOPrivateData
	int nMyField;
OOOPrivateDataEnd

OOODestructor
{
	/* release any assigned memory here */
}
OOODestructorEnd

/* sample method */
OOOMethod(int, getMyField)
{
	/* return a private field */
	return OOOF(nMyField);
}
OOOMethodEnd

/* another sample method */
OOOMethod(int, getData)
{
	/* make a private method call */
	return OOOC(getMyField);
}
OOOMethodEnd

OOOConstructor(int nMyField)
{
	/* interface mapping*/
#define OOOInterface IMyClass
	OOOMapVirtuals
		OOOVirtualMapping(getData)
	OOOMapVirtualsEnd
#undef OOOInterface

	/* export mapping */
	OOOMapMethods
		OOOMethodMapping(getMyField)
	OOOMapMethodsEnd

	/* initialise a private field */
	OOOF(nMyField) = nMyField;
}
OOOConstructorEnd

#undef OOOClass
