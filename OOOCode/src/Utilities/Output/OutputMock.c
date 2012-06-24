#include "OutputMock.h"
#include "OOOCode.h"
#include "stdarg.h"

#define OutputMock_TEMP_MAX_SIZE	4095

#define OOOClass OutputMock

OOOPrivateData
	char szTemp[OutputMock_TEMP_MAX_SIZE + 1];
	char * szBuffer;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOF(szBuffer))
	{
		O_free(OOOF(szBuffer));
	}
}
OOODestructorEnd

OOOMethod(size_t, getMemoryUsed)
{
	size_t uMemoryUsed = 0;
	if (OOOF(szBuffer))
	{
		uMemoryUsed = 4 + O_strlen(OOOF(szBuffer)) + 1;
	}
	return uMemoryUsed;
}
OOOMethodEnd

OOOMethod(void, append, char * szText)
{
	size_t uNewLength = O_strlen(szText);
	if (OOOF(szBuffer))
	{
		uNewLength += O_strlen(OOOF(szBuffer));
		OOOF(szBuffer) = O_realloc(OOOF(szBuffer), uNewLength + 1);
	}
	else
	{
		OOOF(szBuffer) = O_calloc(uNewLength + 1, sizeof(char));
	}
	O_strcat(OOOF(szBuffer), szText);
}
OOOMethodEnd

OOOMethod(void, print, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;
	assert(szMessage);

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOOF(szTemp), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OutputMock_TEMP_MAX_SIZE);

	OOOC(append, OOOF(szTemp));
	O_debug(OOOF(szTemp));
	O_debug("OutputMock: Memory used: %u\n", OOOC(getMemoryUsed));
}
OOOMethodEnd

OOOMethod(bool, check, char * szCompare, ...)
{
	bool bCorrect = (szCompare == NULL);
	if (OOOF(szBuffer))
	{
		if (szCompare)
		{
			va_list aArgs;
			int nLength = 0;

			va_start(aArgs, szCompare);
			nLength = O_vsprintf(OOOF(szTemp), szCompare, aArgs);
			va_end(aArgs);

			/* There is a fixed size buffer for formatting the
			 * message - must ensure we haven't overrun it (no
			 * nicer way of doing this as far as i know) */
			assert(nLength < OutputMock_TEMP_MAX_SIZE);

			bCorrect = (O_strcmp(OOOF(szTemp), OOOF(szBuffer)) == 0);
		}
		else
		{
			bCorrect = FALSE;
		}
		O_free(OOOF(szBuffer));
		OOOF(szBuffer) = NULL;
	}
	return bCorrect;
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface IOutput
	OOOMapVirtuals
		OOOVirtualMapping(print)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
		OOOMethodMapping(check),
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
