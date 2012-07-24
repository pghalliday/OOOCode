#ifndef MockSockets_H
#define MockSockets_H

#include "OOOCode.h"
#include "ISockets.h"
#include "MockLink.h"

#define OOOClass MockSockets
OOODeclare(MockLink * pMockLink)
	OOOImplements
		OOOImplement(ISockets)
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, isBound, o_sock_handle hHandle)
		OOOExport(bool, isConnected, o_sock_handle hHandle)
		OOOExport(bool, connect, o_sock_handle hHandle)
		OOOExport(bool, send, o_sock_handle hHandle, unsigned char * pBuffer, size_t uLength)
		OOOExport(int, receive, o_sock_handle hHandle, unsigned char * pBuffer, size_t uLength)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
