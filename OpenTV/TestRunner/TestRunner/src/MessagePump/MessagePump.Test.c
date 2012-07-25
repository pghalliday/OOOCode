#include "OOOUnitTestDefines.h"
#include "MessagePump.h"

unsigned int MessagePump_Test_uMessageCount = 0;

#define OOOClass MessageHandler
OOODeclare(MessagePump * pMessagePump, unsigned short uMessageClass)
	OOOImplements
		OOOImplement(IMessageHandler)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	MessagePump * pMessagePump;
	unsigned short uMessageClass;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(bool, doMessage, o_message * pMessage)
{
	bool bHandled = FALSE;
	if (O_msg_class(pMessage) == OOOF(uMessageClass))
	{
		switch (O_msg_class(pMessage))
		{
		case 10001:
			OOOCheck(O_msg_type(pMessage) == 10001);
			OOOCheck(MessagePump_Test_uMessageCount == 0);
			MessagePump_Test_uMessageCount++;
			break;
		case 10002:
			OOOCheck(O_msg_type(pMessage) == 10002);
			OOOCheck(MessagePump_Test_uMessageCount == 1);
			MessagePump_Test_uMessageCount++;
			/* Remove this handler and the next message should be ignored */
			OOOCall(OOOF(pMessagePump), removeHandler, OOOCast(IMessageHandler, OOOThis));
			break;
		case 10003:
			OOOCheck(O_msg_type(pMessage) == 10003);
			OOOCheck(MessagePump_Test_uMessageCount == 2);
			MessagePump_Test_uMessageCount++;
			OOOCall(OOOF(pMessagePump), stop);
			break;
		}
		bHandled = TRUE;
	}
	return bHandled;
}
OOOMethodEnd

OOOConstructor(MessagePump * pMessagePump, unsigned short uMessageClass)
{
#define OOOInterface IMessageHandler
	OOOMapVirtuals
		OOOVirtualMapping(doMessage)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(pMessagePump) = pMessagePump;
	OOOF(uMessageClass) = uMessageClass;
}
OOOConstructorEnd
#undef OOOClass

#define OOOClass MessagePumpController
OOODeclare(MessagePump * pMessagePump)
	OOOImplements
		OOOImplement(IMessagePumpController)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	MessagePump * pMessagePump;
	MessageHandler * pMessageHandler1;
	MessageHandler * pMessageHandler2;
	MessageHandler * pMessageHandler3;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOF(pMessageHandler1))
	{
		OOODestroy(OOOF(pMessageHandler1));
	}
	if (OOOF(pMessageHandler2))
	{
		OOODestroy(OOOF(pMessageHandler2));
	}
	if (OOOF(pMessageHandler3))
	{
		OOODestroy(OOOF(pMessageHandler3));
	}
}
OOODestructorEnd

OOOMethod(void, ready)
{
	/* Add a message handler to the message pump */
	OOOF(pMessageHandler1) = OOOConstruct(MessageHandler, OOOF(pMessagePump), 10001);
	OOOF(pMessageHandler2) = OOOConstruct(MessageHandler, OOOF(pMessagePump), 10002);
	OOOF(pMessageHandler3) = OOOConstruct(MessageHandler, OOOF(pMessagePump), 10003);
	OOOCall(OOOF(pMessagePump), addHandler, OOOCast(IMessageHandler, OOOF(pMessageHandler1)));
	OOOCall(OOOF(pMessagePump), addHandler, OOOCast(IMessageHandler, OOOF(pMessageHandler2)));
	OOOCall(OOOF(pMessagePump), addHandler, OOOCast(IMessageHandler, OOOF(pMessageHandler3)));

	/* post a message for the handler to handle */
	{
		o_message tMessage;
		tMessage.msg_class = 10001;
		tMessage.type = 10001;
		assert(O_post_message(&tMessage) == GOOD);
		tMessage.msg_class = 10002;
		tMessage.type = 10002;
		assert(O_post_message(&tMessage) == GOOD);

		/* This message should be ignored as handler for the last message should remove itself */
		tMessage.msg_class = 10002;
		tMessage.type = 10002;
		assert(O_post_message(&tMessage) == GOOD);

		tMessage.msg_class = 10003;
		tMessage.type = 10003;
		assert(O_post_message(&tMessage) == GOOD);
	}
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
