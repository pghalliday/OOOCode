#ifndef MockLink_H
#define MockLink_H

#include "OOOCode.h"
#include "ILink.h"

#define OOOClass MockLink
OOODeclare(unsigned short uMessageClass, unsigned short uMessageType)
	OOOImplements
		OOOImplement(ILink)
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, doMessage, o_message * pMessage)
		OOOExport(bool, isOpen)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
