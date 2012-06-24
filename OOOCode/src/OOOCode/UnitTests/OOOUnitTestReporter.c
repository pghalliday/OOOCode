#include "OOOUnitTestReporter.h"
#include "stdarg.h"

#define OOOUnitTestReporter_LOG_MESSAGE_MAX_SIZE	4095

/* When printing to debug we want something easy to sed */
#define OOOUnitTestReporter_DEBUG_OUTPUT_FORMAT	"BEGIN_UNIT_TEST_OUTPUT\n%s\nEND_UNIT_TEST_OUTPUT\n"

/* XML formats for different types of output */
#define OOOUnitTestReporter_LOG_START_REPORT_FORMAT	"<?xml version \"1.0\"?><REPORT>"
#define OOOUnitTestReporter_LOG_START_TEST_FORMAT		"<TEST name=\"%s\">"
#define OOOUnitTestReporter_LOG_INFORMATION_FORMAT		"<INFORMATION file=\"%s\" line=\"%d\">%s</INFORMATION>"
#define OOOUnitTestReporter_LOG_WARNING_FORMAT			"<WARNING file=\"%s\" line=\"%d\">%s</WARNING>"
#define OOOUnitTestReporter_LOG_ERROR_FORMAT			"<ERROR file=\"%s\" line=\"%d\">%s</ERROR>"
#define OOOUnitTestReporter_MEMORY_LEAK_FORMAT			"<MEMORY_LEAK test=\"%s\" bytes=\"%u\"/>"
#define OOOUnitTestReporter_MEMORY_MAGIC_FORMAT		"<MEMORY_MAGIC test=\"%s\" bytes=\"%u\"/>"
#define OOOUnitTestReporter_LOG_END_TEST_FORMAT		"</TEST>"
#define OOOUnitTestReporter_LOG_END_REPORT_FORMAT		"</REPORT>"

#define OOOClass OOOUnitTestReporter

OOOPrivateData
	OOOIOutput * iOutput;
	char szLogMessage[OOOUnitTestReporter_LOG_MESSAGE_MAX_SIZE + 1];
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, report, char * szText)
{
	/* At the moment we only write to debug in a format that is easy to sed */
	OOOICall(OOOF(iOutput), print, OOOUnitTestReporter_DEBUG_OUTPUT_FORMAT, szText);
}
OOOMethodEnd

OOOMethod(void, startReport)
{
	OOOC(report, OOOUnitTestReporter_LOG_START_REPORT_FORMAT);
}
OOOMethodEnd

OOOMethod(void, startTestReport, char * szName)
{
	char * szText = O_dsprintf(OOOUnitTestReporter_LOG_START_TEST_FORMAT, szName);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, log, OOOUnitTestReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;
	char * szText = NULL;

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOOF(szLogMessage), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OOOUnitTestReporter_LOG_MESSAGE_MAX_SIZE);

	switch (nLogLevel)
	{
	case OOOUnitTestReporter_LogLevel_Information:
		szText = O_dsprintf(OOOUnitTestReporter_LOG_INFORMATION_FORMAT, szFile, nLine, OOOF(szLogMessage));
		break;
	case OOOUnitTestReporter_LogLevel_Warning:
		szText = O_dsprintf(OOOUnitTestReporter_LOG_WARNING_FORMAT, szFile, nLine, OOOF(szLogMessage));
		break;
	case OOOUnitTestReporter_LogLevel_Error:
		szText = O_dsprintf(OOOUnitTestReporter_LOG_ERROR_FORMAT, szFile, nLine, OOOF(szLogMessage));
		break;
	}

	if (szText)
	{
		OOOC(report, szText);
		O_free(szText);
	}
}
OOOMethodEnd

OOOMethod(bool, check, bool bCondition, char * szFile, int nLine, char * szCondition)
{
	if (!bCondition)
	{
		OOOC(log, OOOUnitTestReporter_LogLevel_Error, szFile, nLine, "Failed check: %s", szCondition);
	}
	return bCondition;
}
OOOMethodEnd

OOOMethod(void, memoryLeak, char * szTest, size_t uBytesLost)
{
	char *szText = O_dsprintf(OOOUnitTestReporter_MEMORY_LEAK_FORMAT, szTest, uBytesLost);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, memoryMagic, char * szTest, size_t uBytesGained)
{
	char *szText = O_dsprintf(OOOUnitTestReporter_MEMORY_MAGIC_FORMAT, szTest, uBytesGained);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, endTestReport)
{
	OOOC(report, OOOUnitTestReporter_LOG_END_TEST_FORMAT);
}
OOOMethodEnd

OOOMethod(void, endReport)
{
	OOOC(report, OOOUnitTestReporter_LOG_END_REPORT_FORMAT);
}
OOOMethodEnd

OOOConstructor(OOOIOutput * iOutput)
{
	OOOMapMethods
		OOOMethodMapping(startReport),
		OOOMethodMapping(startTestReport),
		OOOMethodMapping(log),
		OOOMethodMapping(check),
		OOOMethodMapping(memoryLeak),
		OOOMethodMapping(memoryMagic),
		OOOMethodMapping(endTestReport),
		OOOMethodMapping(endReport)
	OOOMapMethodsEnd

	OOOF(iOutput) = iOutput;
}
OOOConstructorEnd

#undef OOOClass
