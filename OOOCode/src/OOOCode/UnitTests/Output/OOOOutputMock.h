#ifndef OOOOutputMock_H
#define OOOOutputMock_H

#include "OOOCode.h"
#include "OOOIOutput.h"

#define OOOClass OOOOutputMock
OOODeclare()
	OOOImplements
		OOOImplement(OOOIOutput);
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, check, char * szCompare, ...);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
