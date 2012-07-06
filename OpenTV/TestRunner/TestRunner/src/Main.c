#include "opentv.h"
#include "assert.h"
#include "OOODebug.h"
#include "OOODebugReporter.h"
#include "OOOUnitTestsRun.h"

#include "Link.h"
#include "Sockets.h"
#include "Listener.h"

void main(void)
{
	/* run the tests first */
	size_t uMemory = O_heap_available();
	OOODebug * pDebug = OOOConstruct(OOODebug);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOIDebug, pDebug));
	OOOUnitTestsRun(OOOCast(OOOIReporter, pReporter));
	OOODestroy(pReporter);
	OOODestroy(pDebug);

	/* Start listening for test requests */
	{
		Link * pLink = OOOConstruct(Link);
		Sockets * pSockets = OOOConstruct(Sockets);
		Listener * pListener = OOOConstruct(Listener, OOOCast(ILink, pLink), OOOCast(ISockets, pSockets));

		/* TODO */

		OOODestroy(pListener);
		OOODestroy(pSockets);
		OOODestroy(pLink);
	}
	assert(O_heap_available() == uMemory);

	/* Stick around so the VSTB does not exit and we know we ran everything */
	while (TRUE)
	{
		o_message tMessage;
		O_ui_get_event_wait(&tMessage);
		if (O_msg_class(&tMessage) == MSG_CLASS_CONTROL)
		{
			if (O_msg_type(&tMessage) == MSG_TYPE_QUIT)
			{
				O_exit();
			}
		}
	}
}
