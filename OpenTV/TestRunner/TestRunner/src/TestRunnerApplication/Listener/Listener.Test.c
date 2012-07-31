#include "OOOUnitTestDefines.h"
#include "Listener.h"
#include "MockLink.h"
#include "MockSockets.h"

#define OOOClass ListenerTest
OOODeclare()
	OOOImplements
		OOOImplement(IMessagePumpController)
		OOOImplement(IListenerController)
		OOOImplement(IRunner)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	MessagePump * pMessagePump;
	MockLink * pLink;
	MockSockets * pSockets;
	Listener * pListener;
OOOPrivateDataEnd

OOODestructor
{
	OOODestroy(OOOF(pMessagePump));
}
OOODestructorEnd

OOOMethod(void, messagePumpStopped)
{
	OOODestroy(OOOF(pListener));
	OOODestroy(OOOF(pSockets));
	OOODestroy(OOOF(pLink));
}
OOOMethodEnd

OOOMethod(void, listenerStopped)
{
	// Stop the message pump
	OOOCall(OOOF(pMessagePump), stop);
}
OOOMethodEnd

OOOMethod(void, run, unsigned char * pData, size_t uSize)
{
	// verify the submitted data
	OOOCheck(O_strcmp(pData, "This is a test") == 0);
	OOOCheck(uSize == (O_strlen("This is a test") + 1));

	// stop the listener
	OOOCall(OOOF(pListener), stop);
}
OOOMethodEnd

OOOMethod(void, listenerStarted)
{
	// start submitting test data for the runner to verify
	MockSocket * pSocket = OOOCall(OOOF(pSockets), connect, 8080);
	OOOCall(pSocket, send, "This is a test", O_strlen("This is a test") + 1);
}
OOOMethodEnd

OOOMethod(void, messagePumpStarted)
{
	OOOF(pLink) = OOOConstruct(MockLink, 10000, 1);
	OOOF(pSockets) = OOOConstruct(MockSockets, OOOF(pLink), 10001);
	OOOF(pListener) = OOOConstruct
			(
					Listener,
					OOOF(pMessagePump),
					OOOCast(ILink, OOOF(pLink)),
					OOOCast(ISockets, OOOF(pSockets)),
					8080,
					OOOCast(IRunner, OOOThis)
			);
	OOOCall(OOOF(pListener), start, OOOCast(IListenerController, OOOThis));
}
OOOMethodEnd

OOOMethod(void, start)
{
	OOOCall(OOOF(pMessagePump), start, OOOCast(IMessagePumpController, OOOThis));
}
OOOMethodEnd

OOOConstructor()
{
#define OOOInterface IMessagePumpController
	OOOMapVirtuals
		OOOVirtualMapping(messagePumpStarted)
		OOOVirtualMapping(messagePumpStopped)
	OOOMapVirtualsEnd
#undef OOOInterface

#define OOOInterface IListenerController
	OOOMapVirtuals
		OOOVirtualMapping(listenerStarted)
		OOOVirtualMapping(listenerStopped)
	OOOMapVirtualsEnd
#undef OOOInterface

#define OOOInterface IRunner
	OOOMapVirtuals
		OOOVirtualMapping(run)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMethodMapping(start)
	OOOMapMethodsEnd

	OOOF(pMessagePump) = OOOConstruct(MessagePump);
}
OOOConstructorEnd
#undef OOOClass

OOOTest(Listener)
{
	ListenerTest * pListenerTest = OOOConstruct(ListenerTest);
	OOOCall(pListenerTest, start);
	OOODestroy(pListenerTest);
}
