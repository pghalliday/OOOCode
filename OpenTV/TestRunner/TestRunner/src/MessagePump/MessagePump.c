#include "MessagePump.h"

#define OOOClass MessagePump

OOOPrivateData
	bool bCanContinue;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, start, IMessagePumpController * iMessagePumpController)
{
	o_message tMessage;
	OOOF(bCanContinue) = TRUE;

	/* Notify controller that we're ready immediately */
	OOOICall(iMessagePumpController, ready);

	/* Wait for events until stopped */
	while (OOOF(bCanContinue))
	{
		O_ui_get_event_wait(&tMessage);
	}
}
OOOMethodEnd

OOOMethod(void, stop)
{
	OOOF(bCanContinue) = FALSE;
}
OOOMethodEnd

OOOConstructor()
{
	OOOMapMethods
		OOOMethodMapping(start)
		OOOMethodMapping(stop)
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
