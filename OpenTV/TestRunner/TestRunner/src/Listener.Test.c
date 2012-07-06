#include "OOOUnitTestDefines.h"
#include "Listener.h"

#include "MockLink.h"
#include "MockSockets.h"

OOOTest(Listener)
{
	MockLink * pLink = OOOConstruct(MockLink, 10000, 1);
	MockSockets * pSockets = OOOConstruct(MockSockets, pLink);
	Listener * pListener = OOOConstruct(Listener, OOOCast(ILink, pLink), OOOCast(ISockets, pSockets));

	/* Check stuff here */
	OOOCheck(OOOCall(pListener, start));

	OOODestroy(pListener);
	OOODestroy(pSockets);
	OOODestroy(pLink);
}
