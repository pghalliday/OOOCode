#include "Listener.h"

#define OOOClass Listener

OOOPrivateData
	MessagePump * pMessagePump;
	ILink * iLink;
	ISockets * iSockets;
	unsigned short uPort;
	IRunner * iRunner;
	IListenerController * iListenerController;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, stop)
{

}
OOOMethodEnd

OOOMethod(void, start, IListenerController * iListenerController)
{
	OOOF(iListenerController) = iListenerController;
}
OOOMethodEnd

OOOConstructor(MessagePump * pMessagePump, ILink * iLink, ISockets * iSockets, unsigned short uPort, IRunner * iRunner)
{
	OOOMapMethods
		OOOMethodMapping(start)
		OOOMethodMapping(stop)
	OOOMapMethodsEnd

	OOOF(pMessagePump) = pMessagePump;
	OOOF(iLink) = iLink;
	OOOF(iSockets) = iSockets;
	OOOF(uPort) = uPort;
	OOOF(iRunner) = iRunner;
}
OOOConstructorEnd

#undef OOOClass
