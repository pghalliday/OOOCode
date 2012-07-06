#include "Listener.h"

#define OOOClass Listener

OOOPrivateData
	ILink * iLink;
	ISockets * iSockets;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(bool, start)
{
	return TRUE;
}
OOOMethodEnd

OOOConstructor(ILink * iLink, ISockets * iSockets)
{
	OOOMapMethods
		OOOMethodMapping(start)
	OOOMapMethodsEnd

	OOOF(iLink) = iLink;
	OOOF(iSockets) = iSockets;
}
OOOConstructorEnd

#undef OOOClass
