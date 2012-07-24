#include "MockSockets.h"

#define OOOClass MockSockets

#define MockSockets_SOCKET_HANDLE			1
#define MockSockets_WAITING_SOCKET_HANDLE	2

OOOPrivateData
	MockLink * pMockLink;
	bool bIsBound;
	bool bIsConnected;
	unsigned char * pReceivedData;
	size_t uReceivedDataLength;
	unsigned char * pSentData;
	size_t uSentDataLength;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(o_sock_handle, create, int nAf, int nType, int nProtocol)
{
	return MockSockets_SOCKET_HANDLE;
}
OOOMethodEnd

OOOMethod(bool, isBound, o_sock_handle hHandle)
{
	bool bIsBound = FALSE;
	if (hHandle == MockSockets_SOCKET_HANDLE)
	{
		bIsBound = OOOF(bIsBound);
	}
	return bIsBound;
}
OOOMethodEnd

OOOMethod(o_sock_error, bind, o_sock_handle hHandle, o_sockaddr * pAddress, size_t uAddressLength)
{
	o_sock_error nError = O_ERR_SOCK_WRONG_STATE;
	if (OOOCall(OOOF(pMockLink), isOpen))
	{
		if (hHandle == MockSockets_SOCKET_HANDLE)
		{
			if (!OOOC(isBound, hHandle))
			{
				nError = O_ERR_SOCK_NO_ERROR;
				OOOF(bIsBound) = TRUE;
			}
		}
	}
	return nError;
}
OOOMethodEnd

OOOMethod(o_sock_handle, accept, o_sock_handle hHandle)
{
	o_sock_handle hWaitingHandle = ILLEGAL_HANDLE;
	if (hHandle == MockSockets_SOCKET_HANDLE)
	{
		if (OOOC(isBound, hHandle))
		{
			hWaitingHandle = MockSockets_WAITING_SOCKET_HANDLE;
		}
	}
	return hWaitingHandle;
}
OOOMethodEnd

OOOMethod(bool, isConnected, o_sock_handle hHandle)
{
	bool bIsConnected = FALSE;
	if (hHandle == MockSockets_WAITING_SOCKET_HANDLE)
	{
		bIsConnected = OOOF(bIsConnected);
	}
	return bIsConnected;
}
OOOMethodEnd

OOOMethod(bool, connect, o_sock_handle hHandle)
{
	bool bIsConnected = FALSE;
	if (hHandle == MockSockets_WAITING_SOCKET_HANDLE)
	{
		/* post the connected message */
		o_message tMessage;
		tMessage.msg_class = MSG_CLASS_SOCKET;
		tMessage.type = MSG_TYPE_SOCK_CONNECTED;
		tMessage.INFO_SOCK_HANDLE = MockSockets_WAITING_SOCKET_HANDLE;
		assert(O_post_message(&tMessage) == GOOD);

		OOOF(bIsConnected) = TRUE;
		bIsConnected = TRUE;
	}
	return bIsConnected;
}
OOOMethodEnd

OOOMethod(bool, send, o_sock_handle hHandle, unsigned char * pBuffer, size_t uLength)
{
	bool bIsWritten = FALSE;
	if (OOOC(isConnected, hHandle))
	{
		o_message tMessage;

		/* buffer the data */
		if (OOOF(pReceivedData))
		{
			O_free(OOOF(pReceivedData));
		}
		OOOF(pReceivedData) = O_malloc(uLength);
		O_memcpy(OOOF(pReceivedData), pBuffer, uLength);
		OOOF(uReceivedDataLength) = uLength;

		/* post the read notify message */
		tMessage.msg_class = MSG_CLASS_SOCKET;
		tMessage.type = MSG_TYPE_SOCK_READ_NFY;
		tMessage.INFO_SOCK_HANDLE = MockSockets_WAITING_SOCKET_HANDLE;
		assert(O_post_message(&tMessage) == GOOD);
		bIsWritten = TRUE;
	}
	return bIsWritten;
}
OOOMethodEnd

OOOMethod(int, read, o_sock_handle hHandle, void * pBuffer, size_t uLength)
{
	int nBytesRead = 0;
	if (OOOF(pReceivedData))
	{
		if (OOOF(uReceivedDataLength) > uLength)
		{
			unsigned char * pCurrentData = OOOF(pReceivedData);
			O_memcpy(pBuffer, pCurrentData, uLength);
			OOOF(uReceivedDataLength) -= uLength;
			OOOF(pReceivedData) = O_malloc(OOOF(uReceivedDataLength));
			O_memcpy(OOOF(pReceivedData), pCurrentData + uLength, OOOF(uReceivedDataLength));
			O_free(pCurrentData);
			nBytesRead = uLength;
		}
		else
		{
			O_memcpy(pBuffer, OOOF(pReceivedData), OOOF(uReceivedDataLength));
			O_free(OOOF(pReceivedData));
			OOOF(pReceivedData) = NULL;
			nBytesRead = OOOF(uReceivedDataLength);
			OOOF(uReceivedDataLength) = 0;
		}
	}
	return nBytesRead;
}
OOOMethodEnd

OOOMethod(o_sock_error, write, o_sock_handle hHandle, void * pBuffer, size_t uLength)
{
	o_sock_error nError = O_ERR_SOCK_WRONG_STATE;
	if (OOOC(isConnected, hHandle))
	{
		o_message tMessage;

		/* buffer the data */
		if (OOOF(pSentData))
		{
			O_free(OOOF(pSentData));
		}
		OOOF(pSentData) = O_malloc(uLength);
		O_memcpy(OOOF(pSentData), pBuffer, uLength);
		OOOF(uSentDataLength) = uLength;

		/* post the read notify message */
		tMessage.msg_class = MSG_CLASS_SOCKET;
		tMessage.type = MSG_TYPE_SOCK_WRITE_NFY;
		tMessage.INFO_SOCK_HANDLE = MockSockets_WAITING_SOCKET_HANDLE;
		assert(O_post_message(&tMessage) == GOOD);
		nError = O_ERR_SOCK_NO_ERROR;
	}
	return nError;
}
OOOMethodEnd

OOOMethod(int, receive, o_sock_handle hHandle, unsigned char * pBuffer, size_t uLength)
{
	int nBytesRead = 0;
	if (OOOF(pSentData))
	{
		if (OOOF(uSentDataLength) > uLength)
		{
			unsigned char * pCurrentData = OOOF(pSentData);
			O_memcpy(pBuffer, pCurrentData, uLength);
			OOOF(uSentDataLength) -= uLength;
			OOOF(pSentData) = O_malloc(OOOF(uSentDataLength));
			O_memcpy(OOOF(pSentData), pCurrentData + uLength, OOOF(uSentDataLength));
			O_free(pCurrentData);
			nBytesRead = uLength;
		}
		else
		{
			O_memcpy(pBuffer, OOOF(pSentData), OOOF(uSentDataLength));
			O_free(OOOF(pSentData));
			OOOF(pSentData) = NULL;
			nBytesRead = OOOF(uSentDataLength);
			OOOF(uSentDataLength) = 0;
		}
	}
	return nBytesRead;
}
OOOMethodEnd

OOOConstructor(MockLink * pMockLink)
{
#define OOOInterface ISockets
	OOOMapVirtuals
		OOOVirtualMapping(create)
		OOOVirtualMapping(bind)
		OOOVirtualMapping(accept)
		OOOVirtualMapping(read)
		OOOVirtualMapping(write)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMethodMapping(isBound)
		OOOMethodMapping(isConnected)
		OOOMethodMapping(connect)
		OOOMethodMapping(send)
		OOOMethodMapping(receive)
	OOOMapMethodsEnd

	OOOF(pMockLink) = pMockLink;
}
OOOConstructorEnd

#undef OOOClass
