#include "OOOUnitTestDefines.h"
#include "MockSockets.h"
#include "MockLink.h"

#define TEST_STRING_1		"This string is an exact multiple of the buffer size..."
#define TEST_STRING_2		"This string is not an exact multiple of the buffer size"
#define TEST_BUFFER_SIZE	5
#define	TEST_MSG_CLASS		10001

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
	MockSocket * pSocket = NULL;

	MockLink * pMockLink = OOOConstruct(MockLink, 10000, 1);
	MockSockets * pMockSockets = OOOConstruct(MockSockets, pMockLink, TEST_MSG_CLASS);

	ILink * iLink = OOOCast(ILink, pMockLink);
	ISockets * iSockets = OOOCast(ISockets, pMockSockets);

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
					/* should be able to create a TCP socket */
					hSocket = OOOICall(iSockets, create, AF_INET, SOCK_STREAM, 0);
					OOOCheck(hSocket != ILLEGAL_HANDLE);

					/* should be able to bind a socket now */
					if (OOOCheck(OOOICall(iSockets, bind, hSocket, &tAddress, sizeof(tAddress)) == O_ERR_SOCK_NO_ERROR))
					{
						/* should be able to accept connections now */
						hWaitingSocket = OOOICall(iSockets, accept, hSocket);
						if (OOOCheck(hWaitingSocket != ILLEGAL_HANDLE))
						{
							/* connect to the waiting socket */
							pSocket = OOOCall(pMockSockets, connect, 80);
							if (!OOOCheck(pSocket != NULL))
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
					if (tMessage.INFO_SOCK_HANDLE == hWaitingSocket)
					{
						/* send some data to the socket */
						OOOCheck(OOOCall(pSocket, send, TEST_STRING_1, O_strlen(TEST_STRING_1) + 1));
					}
				}
				if (O_msg_class(&tMessage) == MSG_CLASS_SOCKET && O_msg_type(&tMessage) == MSG_TYPE_SOCK_READ_NFY)
				{
					if (tMessage.INFO_SOCK_HANDLE == hWaitingSocket)
					{
						o_sock_error nError;

						/* read the data back */
						char * szTest = O_malloc(O_strlen(TEST_STRING_1) + 1);
						char szBuffer[TEST_BUFFER_SIZE] = {0};
						int nTotalBytesRead = 0;
						int nBytesRead = 0;
						do
						{
							nBytesRead = OOOICall(iSockets, read, hWaitingSocket, szBuffer, TEST_BUFFER_SIZE);
							O_memcpy(szTest + nTotalBytesRead, szBuffer, nBytesRead);
							nTotalBytesRead += nBytesRead;
						}
						while (nBytesRead == TEST_BUFFER_SIZE);
						OOOCheck(nTotalBytesRead == O_strlen(TEST_STRING_1) + 1);
						OOOCheck(O_strcmp(TEST_STRING_1, szTest) == 0);
						O_free(szTest);

						/* write a response */
						nError = OOOICall(iSockets, write, hWaitingSocket, TEST_STRING_2, O_strlen(TEST_STRING_2) + 1);
						OOOCheck(O_ERR_SOCK_NO_ERROR == nError);
					}
				}
				if (O_msg_class(&tMessage) == TEST_MSG_CLASS && O_msg_type(&tMessage) == MockSocket_MSG_TYPE_SEND_NFY)
				{
					if (tMessage.info.vfp[0] == pSocket)
					{
						// do nothing
					}
				}
				if (O_msg_class(&tMessage) == TEST_MSG_CLASS && O_msg_type(&tMessage) == MockSocket_MSG_TYPE_RECEIVE_NFY)
				{
					if (tMessage.info.vfp[0] == pSocket)
					{
						char * szTest = O_malloc(O_strlen(TEST_STRING_2) + 1);
						char szBuffer[TEST_BUFFER_SIZE] = {0};
						int nTotalBytesRead = 0;
						int nBytesRead = 0;
						do
						{
							nBytesRead = OOOCall(pSocket, receive, szBuffer, TEST_BUFFER_SIZE);
							O_memcpy(szTest + nTotalBytesRead, szBuffer, nBytesRead);
							nTotalBytesRead += nBytesRead;
						}
						while (nBytesRead == TEST_BUFFER_SIZE);
						OOOCheck(nTotalBytesRead == O_strlen(TEST_STRING_2) + 1);
						OOOCheck(O_strcmp(TEST_STRING_2, szTest) == 0);
						O_free(szTest);
					}
				}
				if (O_msg_class(&tMessage) == MSG_CLASS_SOCKET && O_msg_type(&tMessage) == MSG_TYPE_SOCK_WRITE_NFY)
				{
					if (tMessage.INFO_SOCK_HANDLE == hWaitingSocket)
					{
						break;
					}
				}
			}
		}
	}

	OOODestroy(pMockSockets);
	OOODestroy(pMockLink);
}
