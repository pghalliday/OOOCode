#include "OOOUnitTestDefines.h"
#include "MockSockets.h"
#include "MockLink.h"

OOOTest(MockSockets)
{
	o_sock_handle hSocket;
	o_sock_handle hWaitingSocket = ILLEGAL_HANDLE;
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

						/* should not be be accepting connection on port 80 yet */
						/*OOOCheck(!OOOCall(pMockSockets, isAcceptingConnections, 80));*/

						/* should be able to accept connections now */
						hWaitingSocket = OOOICall(iSockets, accept, hSocket);
						if (OOOCheck(hWaitingSocket != ILLEGAL_HANDLE))
						{
							/* should be accepting connection on port 80 now */
							/*OOOCheck(OOOCall(pMockSockets, isAcceptingConnections, 80));*/

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
					/* check the message contains the correct socket */
					OOOCheck(tMessage.INFO_SOCK_HANDLE == hWaitingSocket);

					/* should be connected now */
					OOOCheck(OOOCall(pMockSockets, isConnected, hWaitingSocket));

					/* send some data to the socket */
					OOOCheck(OOOCall(pMockSockets, send, hWaitingSocket, "This is a test", O_strlen("This is a test") + 1));
				}
				if (O_msg_class(&tMessage) == MSG_CLASS_SOCKET && O_msg_type(&tMessage) == MSG_TYPE_SOCK_READ_NFY)
				{
					o_sock_error nError;
					char szReadData[100];

					/* read the data back in one go */
					OOOCheck(OOOICall(iSockets, read, hWaitingSocket, szReadData, 100) == O_strlen("This is a test") + 1);
					OOOCheck(O_strcmp(szReadData, "This is a test") == 0);

					/* write a response */
					nError = OOOICall(iSockets, write, hWaitingSocket, "This is a test too", O_strlen("This is a test too") + 1);
					OOOCheck(O_ERR_SOCK_NO_ERROR == nError);
				}
				if (O_msg_class(&tMessage) == MSG_CLASS_SOCKET && O_msg_type(&tMessage) == MSG_TYPE_SOCK_WRITE_NFY)
				{
					char szWrittenData[100];
					OOOCheck(OOOCall(pMockSockets, receive, hWaitingSocket, szWrittenData, 100) == O_strlen("This is a test too") + 1);
					OOOCheck(O_strcmp(szWrittenData, "This is a test too") == 0);
					break;
				}
			}
		}
	}

	OOODestroy(pMockSockets);
	OOODestroy(pMockLink);
}
