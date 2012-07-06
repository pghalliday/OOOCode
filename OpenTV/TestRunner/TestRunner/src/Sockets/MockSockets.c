#include "MockSockets.h"

#define OOOClass MockSockets

#define MockSockets_SOCKET_HANDLE			1
#define MockSockets_WAITING_SOCKET_HANDLE	2

OOOPrivateData
	MockLink * pMockLink;
	bool bIsBound;
	bool bIsConnected;
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

OOOConstructor(MockLink * pMockLink)
{
#define OOOInterface ISockets
	OOOMapVirtuals
		OOOVirtualMapping(create)
		OOOVirtualMapping(bind)
		OOOVirtualMapping(accept)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMethodMapping(isBound)
		OOOMethodMapping(isConnected)
		OOOMethodMapping(connect)
	OOOMapMethodsEnd

	OOOF(pMockLink) = pMockLink;
}
OOOConstructorEnd

#undef OOOClass
