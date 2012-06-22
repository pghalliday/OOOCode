#include "OutputMock.h"
#include "OOOCode.h"
#include "stdarg.h"

#define OutputDebug_LOG_MESSAGE_MAX_SIZE	4095

#define OOOClass OutputMock

OOOPrivateData
	char szLogMessage[OutputDebug_LOG_MESSAGE_MAX_SIZE + 1];
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

OOOMethod(void, append)
{
	size_t uNewLength = O_strlen(OOOF(szLogMessage));
	if (OOOF(szBuffer))
	{
		uNewLength += O_strlen(OOOF(szBuffer));
		OOOF(szBuffer) = O_realloc(OOOF(szBuffer), uNewLength + 1);
	}
	else
	{
		OOOF(szBuffer) = O_calloc(uNewLength + 1, sizeof(char));
	}
	O_strcat(OOOF(szBuffer), OOOF(szLogMessage));
}
OOOMethodEnd

OOOMethod(void, print, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;
	assert(szMessage);

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOOF(szLogMessage), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OutputDebug_LOG_MESSAGE_MAX_SIZE);

	OOOC(append);
	O_debug(OOOF(szLogMessage));
}
OOOMethodEnd

OOOMethod(bool, check, char * szCompare);
{
	bool bCorrect = (szCompare == NULL);
	if (OOOF(szBuffer))
	{
		if (szCompare)
		{
			bCorrect = (O_strcmp(szCompare, OOOF(szBuffer)) == 0);
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
		OOOMethodMapping(check)
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
