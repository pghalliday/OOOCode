#ifndef Listener_H
#define Listener_H

#include "OOOCode.h"
#include "ILink.h"
#include "ISockets.h"

#define OOOClass Listener
OOODeclare(ILink * iLink, ISockets * iSockets, unsigned short uPort)
	OOOImplements
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
