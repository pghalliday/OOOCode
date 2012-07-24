#include "MockSockets.h"

#define OOOClass MockSockets

#define MockSockets_SOCKET_HANDLE			1
#define MockSockets_WAITING_SOCKET_HANDLE	2

OOOPrivateData
	MockLink * pMockLink;
	bool bIsBound;
	bool bIsConnected;
	unsigned char * pData;
	size_t uLength;
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

OOOMethod(bool, send, o_sock_handle hHandle, unsigned char * pData, size_t uLength)
{
	bool bIsWritten = FALSE;
	if (OOOC(isConnected, hHandle))
	{
		o_message tMessage;

		/* buffer the data */
		if (OOOF(pData))
		{
			O_free(OOOF(pData));
		}
		OOOF(pData) = O_malloc(uLength);
		O_memcpy(OOOF(pData), pData, uLength);
		OOOF(uLength) = uLength;

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
	if (OOOF(pData))
	{
		if (OOOF(uLength) > uLength)
		{
			unsigned char * pCurrentData = OOOF(pData);
			O_memcpy(pBuffer, pCurrentData, uLength);
			OOOF(uLength) -= uLength;
			OOOF(pData) = O_malloc(OOOF(uLength));
			O_memcpy(OOOF(pData), pCurrentData + uLength, OOOF(uLength));
			O_free(pCurrentData);
			nBytesRead = uLength;
		}
		else
		{
			O_memcpy(pBuffer, OOOF(pData), OOOF(uLength));
			O_free(OOOF(pData));
			OOOF(pData) = NULL;
			OOOF(uLength) = 0;
			nBytesRead = OOOF(uLength);
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
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMethodMapping(isBound)
		OOOMethodMapping(isConnected)
		OOOMethodMapping(connect)
		OOOMethodMapping(send)
	OOOMapMethodsEnd

	OOOF(pMockLink) = pMockLink;
}
OOOConstructorEnd

#undef OOOClass
