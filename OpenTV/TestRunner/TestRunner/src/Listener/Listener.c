#include "Listener.h"

#define OOOClass Listener

OOOPrivateData
	ILink * iLink;
	ISockets * iSockets;
	unsigned short uPort;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd


OOOConstructor(ILink * iLink, ISockets * iSockets, unsigned short uPort)
{
	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(iLink) = iLink;
	OOOF(iSockets) = iSockets;
	OOOF(uPort) = uPort;
}
OOOConstructorEnd

#undef OOOClass
