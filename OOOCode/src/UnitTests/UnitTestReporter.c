#include "UnitTestReporter.h"
#include "stdarg.h"

#define UnitTestReporter_LOG_MESSAGE_MAX_SIZE	4095

/* When printing to debug we want something easy to sed */
#define UnitTestReporter_DEBUG_OUTPUT_FORMAT	"BEGIN_UNIT_TEST_OUTPUT\n%s\nEND_UNIT_TEST_OUTPUT\n"

/* XML formats for different types of output */
#define UnitTestReporter_LOG_START_REPORT_FORMAT	"<?xml version \"1.0\"?><REPORT>"
#define UnitTestReporter_LOG_START_TEST_FORMAT		"<TEST name=\"%s\">"
#define UnitTestReporter_LOG_INFORMATION_FORMAT		"<INFORMATION file=\"%s\" line=\"%d\">%s</INFORMATION>"
#define UnitTestReporter_LOG_WARNING_FORMAT			"<WARNING file=\"%s\" line=\"%d\">%s</WARNING>"
#define UnitTestReporter_LOG_ERROR_FORMAT			"<ERROR file=\"%s\" line=\"%d\">%s</ERROR>"
#define UnitTestReporter_LOG_END_TEST_FORMAT		"</TEST>"
#define UnitTestReporter_LOG_END_REPORT_FORMAT		"</REPORT>"

#define OOOClass UnitTestReporter

OOOPrivateData
	IOutput * iOutput;
	char szLogMessage[UnitTestReporter_LOG_MESSAGE_MAX_SIZE + 1];
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, report, char * szText)
{
	/* At the moment we only write to debug in a format that is easy to sed */
	OOOICall(OOO(iOutput), print, UnitTestReporter_DEBUG_OUTPUT_FORMAT, szText);
}
OOOMethodEnd

OOOMethod(void, startReport)
{
	OOOPCall(OOOThis, report, UnitTestReporter_LOG_START_REPORT_FORMAT);
}
OOOMethodEnd

OOOMethod(void, startTestReport, char * szName)
{
	char * szText = O_dsprintf(UnitTestReporter_LOG_START_TEST_FORMAT, szName);
	OOOPCall(OOOThis, report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, log, UnitTestReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;
	char * szText = NULL;

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOO(szLogMessage), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < UnitTestReporter_LOG_MESSAGE_MAX_SIZE);

	switch (nLogLevel)
	{
	case UnitTestReporter_LogLevel_Information:
		szText = O_dsprintf(UnitTestReporter_LOG_INFORMATION_FORMAT, szFile, nLine, OOO(szLogMessage));
		break;
	case UnitTestReporter_LogLevel_Warning:
		szText = O_dsprintf(UnitTestReporter_LOG_WARNING_FORMAT, szFile, nLine, OOO(szLogMessage));
		break;
	case UnitTestReporter_LogLevel_Error:
		szText = O_dsprintf(UnitTestReporter_LOG_ERROR_FORMAT, szFile, nLine, OOO(szLogMessage));
		break;
	}

	if (szText)
	{
		OOOPCall(OOOThis, report, szText);
		O_free(szText);
	}
}
OOOMethodEnd

OOOMethod(bool, check, bool bCondition, char * szFile, int nLine, char * szCondition)
{
	if (!bCondition)
	{
		OOOPCall(OOOThis, log, UnitTestReporter_LogLevel_Error, szFile, nLine, "Failed check: %s", szCondition);
	}
	return bCondition;
}
OOOMethodEnd

OOOMethod(void, endTestReport)
{
	OOOPCall(OOOThis, report, UnitTestReporter_LOG_END_TEST_FORMAT);
}
OOOMethodEnd

OOOMethod(void, endReport)
{
	OOOPCall(OOOThis, report, UnitTestReporter_LOG_END_REPORT_FORMAT);
}
OOOMethodEnd

OOOConstructor(IOutput * iOutput)
{
	OOOMapMethods
		OOOMethodMapping(startReport),
		OOOMethodMapping(startTestReport),
		OOOMethodMapping(log),
		OOOMethodMapping(check),
		OOOMethodMapping(endTestReport),
		OOOMethodMapping(endReport)
	OOOMapMethodsEnd

	OOO(iOutput) = iOutput;
}
OOOConstructorEnd

#undef OOOClass
