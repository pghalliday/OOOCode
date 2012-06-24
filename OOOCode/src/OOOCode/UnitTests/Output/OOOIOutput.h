#ifndef OOOIOutput_H
#define OOOIOutput_H

#include "OOOCode.h"

#define OOOInterface OOOIOutput
OOOVirtuals
	OOOVirtual(void, print, char * szMessage, ...);
OOOVirtualsEnd
#undef OOOInterface

#endif
