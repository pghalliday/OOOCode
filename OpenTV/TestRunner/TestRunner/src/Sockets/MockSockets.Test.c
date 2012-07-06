#include "OOOUnitTestDefines.h"
#include "MockSockets.h"
#include "MockLink.h"

OOOTest(MockSockets)
{
	o_sock_handle hSocket;
	o_sock_handle hWaitingSocket;
	o_ip_addr tAddress =
			{
				AF_INET,
				80,
				0
			};
	o_link_error nError;
	o_link_type nLinkType = O_LINK_TYPE_DEFAULT;
	char * szModuleName = "Test";
	char * szLinkOptions = "Test";
	unsigned int uTimeout = 20;
	o_message tMessage;

	MockLink * pMockLink = OOOConstruct(MockLink, 10000, 1);
	MockSockets * pMockSockets = OOOConstruct(MockSockets, pMockLink);

	ILink * iLink = OOOCast(ILink, pMockLink);
	ISockets * iSockets = OOOCast(ISockets, pMockSockets);

	/* should be able to create a TCP socket before we open the link (I think) */
	hSocket = OOOICall(iSockets, create, AF_INET, SOCK_STREAM, 0);
	OOOCheck(hSocket != ILLEGAL_HANDLE);

	/* Should not be bound */
	OOOCheck(!OOOCall(pMockSockets, isBound, hSocket));

	/* should not be able to bind a socket yet */
	OOOCheck(OOOICall(iSockets, bind, hSocket, &tAddress, sizeof(tAddress)) == O_ERR_SOCK_WRONG_STATE);

	/* Should not be bound */
	OOOCheck(!OOOCall(pMockSockets, isBound, hSocket));

	nError = OOOICall(iLink, open, nLinkType, szModuleName, szLinkOptions, uTimeout);
	if (OOOCheck(nError == O_LINK_ERR_NO_ERROR))
	{
		/* wait for the link up message */
		while (TRUE)
		{
			O_ui_get_event_wait(&tMessage);
			if (!OOOCall(pMockLink, doMessage, &tMessage))
			{
				if (O_msg_class(&tMessage) == MSG_CLASS_COMM && O_msg_type(&tMessage) == MSG_TYPE_LINK_UP)
				{
					/* should be able to bind a socket now */
					if (OOOCheck(OOOICall(iSockets, bind, hSocket, &tAddress, sizeof(tAddress)) == O_ERR_SOCK_NO_ERROR))
					{
						/* Should be bound */
						OOOCheck(OOOCall(pMockSockets, isBound, hSocket));

						/* should be able to accept connections now */
						hWaitingSocket = OOOICall(iSockets, accept, hSocket);
						if (!OOOCheck(hWaitingSocket != ILLEGAL_HANDLE))
						{
							/* should not be connected yet */
							OOOCheck(!OOOCall(pMockSockets, isConnected, hWaitingSocket));

							/* connect to the waiting socket */
							if (!OOOCheck(OOOCall(pMockSockets, connect, hWaitingSocket)))
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
				if (O_msg_class(&tMessage) == MSG_CLASS_SOCKET && O_msg_type(&tMessage) == MSG_TYPE_SOCK_CONNECTED)
				{
					/* check the message contains the corrcet socket */
					OOOCheck(tMessage.INFO_SOCK_HANDLE == hWaitingSocket);

					/* should be connected now */
					OOOCheck(OOOCall(pMockSockets, isConnected, hWaitingSocket));

					break;
				}
			}
		}
	}

	OOODestroy(pMockSockets);
	OOODestroy(pMockLink);
}
