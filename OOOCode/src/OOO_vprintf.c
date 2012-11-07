#include "OOO_vprintf.h"
#include "assert.h"

#ifndef OOO_VPRINTF_BUFFER_SIZE
#define OOO_VPRINTF_BUFFER_SIZE	(4*1024) /* default to 4KB buffer*/
#endif

char OOO_vprintf_szBuffer[OOO_VPRINTF_BUFFER_SIZE];

void OOO_vprintf(char * szMessage, va_list aArgs)
{
	int nMessageLength = O_vsprintf(OOO_vprintf_szBuffer, szMessage, aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OOO_VPRINTF_BUFFER_SIZE - 1);
}
