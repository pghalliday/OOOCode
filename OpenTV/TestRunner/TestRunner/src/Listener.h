#ifndef Listener_H
#define Listener_H

#include "OOOCode.h"
#include "ILink.h"
#include "ISockets.h"

#define OOOClass Listener
OOODeclare(ILink * iLink, ISockets * iSockets)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, start)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
