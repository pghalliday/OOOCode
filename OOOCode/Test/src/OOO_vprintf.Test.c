#include "OOOUnitTestDefines.h"
#include "OOO_vprintf.h"

static void testFunction(char * szMessage, ...)
{
	va_list aArgs;
	va_start(aArgs, szMessage);
	OOO_vprintf(szMessage, aArgs);
	va_end(aArgs);
}

OOOTest(OOO_vprintf)
{
	testFunction("%s%u%s%d", "hello", 1234, "goodbye", -567);
	OOOCheck(O_strcmp(OOO_vprintf_szBuffer, "hello1234goodbye-567") == 0);
}
