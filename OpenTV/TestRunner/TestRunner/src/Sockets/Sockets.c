#include "Sockets.h"

#define OOOClass Sockets

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOConstructor()
{
#define OOOInterface ISockets
	OOOMapVirtuals
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
