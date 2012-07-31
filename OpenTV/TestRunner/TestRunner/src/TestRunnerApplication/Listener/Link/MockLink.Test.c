#include "OOOUnitTestDefines.h"
#include "MockLink.h"

OOOTest(MockLink)
{
	o_link_error nError;
	o_link_type nLinkType = O_LINK_TYPE_DEFAULT;
	char * szModuleName = "Test";
	char * szLinkOptions = "Test";
	unsigned int uTimeout = 20;
	o_message tMessage;

	MockLink * pMockLink = OOOConstruct(MockLink, 10000, 1);
	ILink * iLink = OOOCast(ILink, pMockLink);

	/* link should not be open */
	OOOCheck(!OOOCall(pMockLink, isOpen));

	nError = OOOICall(iLink, open, nLinkType, szModuleName, szLinkOptions, uTimeout);
	if (OOOCheck(nError == O_LINK_ERR_NO_ERROR))
	{
		/* should still not be open */
		OOOCheck(!OOOCall(pMockLink, isOpen));

		/* wait for the link up message */
		while (TRUE)
		{
			O_ui_get_event_wait(&tMessage);
			if (!OOOCall(pMockLink, doMessage, &tMessage))
			{
				if (O_msg_class(&tMessage) == MSG_CLASS_COMM && O_msg_type(&tMessage) == MSG_TYPE_LINK_UP)
				{
					/* should be open now */
					OOOCheck(OOOCall(pMockLink, isOpen));
					break;
				}
			}
		}
	}

	OOODestroy(pMockLink);
}
