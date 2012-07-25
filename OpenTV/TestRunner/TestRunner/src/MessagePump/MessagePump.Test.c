#include "OOOUnitTestDefines.h"
#include "MessagePump.h"

#define OOOClass MessagePumpController
OOODeclare()
	OOOImplements
		OOOImplement(IMessagePumpController)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	MessagePump * pMessagePump;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, ready)
{
	/* Stop the message pump */
	OOOCall(OOOF(pMessagePump), stop);
}
OOOMethodEnd

OOOConstructor(MessagePump * pMessagePump)
{
#define OOOInterface IMessagePumpController
	OOOMapVirtuals
		OOOVirtualMapping(ready)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(pMessagePump) = pMessagePump;
}
OOOConstructorEnd
#undef OOOClass

OOOTest(MessagePump)
{
	MessagePump * pMessagePump = OOOConstruct(MessagePump);
	MessagePumpController * pMessagePumpController = OOOConstruct(MessagePumpController, pMessagePump);

	/* Check stuff here */
	OOOCheck(pMessagePump != NULL);

	/* Start the message pump */
	OOOCall(pMessagePump, start, OOOCast(IMessagePumpController, pMessagePumpController));

	OOODestroy(pMessagePumpController);
	OOODestroy(pMessagePump);
	pMessagePump = NULL;
}
