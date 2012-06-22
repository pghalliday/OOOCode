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
	if (OOO(szBuffer))
	{
		O_free(OOO(szBuffer));
	}
}
OOODestructorEnd

OOOMethod(void, append)
{
	size_t uNewLength = O_strlen(OOO(szLogMessage));
	if (OOO(szBuffer))
	{
		uNewLength += O_strlen(OOO(szBuffer));
		OOO(szBuffer) = O_realloc(OOO(szBuffer), uNewLength + 1);
	}
	else
	{
		OOO(szBuffer) = O_calloc(uNewLength + 1, sizeof(char));
	}
	O_strcat(OOO(szBuffer), OOO(szLogMessage));
}
OOOMethodEnd

OOOMethod(void, print, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;
	assert(szMessage);

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOO(szLogMessage), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OutputDebug_LOG_MESSAGE_MAX_SIZE);

	OOOPCall(OOOThis, append);
	O_debug(OOO(szLogMessage));
}
OOOMethodEnd

OOOMethod(bool, check, char * szCompare);
{
	bool bCorrect = (szCompare == NULL);
	if (OOO(szBuffer))
	{
		if (szCompare)
		{
			bCorrect = (O_strcmp(szCompare, OOO(szBuffer)) == 0);
		}
		else
		{
			bCorrect = FALSE;
		}
		O_free(OOO(szBuffer));
		OOO(szBuffer) = NULL;
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
