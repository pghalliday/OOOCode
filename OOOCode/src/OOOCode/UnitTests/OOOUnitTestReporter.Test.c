#include "OOOUnitTestDefines.h"

#include "OOOOutputMock.h"
#include "OOOUnitTestReporter.h"

OOOTest(OOOUnitTestReporter)
{
	OOOOutputMock * pOutputMock = OOOConstruct(OOOOutputMock);
	OOOUnitTestReporter * pReporter = OOOConstruct(OOOUnitTestReporter, OOOCast(OOOIOutput, pOutputMock));

	OOOCall(pReporter, startReport);
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<?xml version \"1.0\"?><REPORT>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, startTestReport, "My Test");
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, log, OOOUnitTestReporter_LogLevel_Information, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<INFORMATION file=\"My File\" line=\"10\">Test Information: Hello: 55</INFORMATION>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, log, OOOUnitTestReporter_LogLevel_Warning, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<WARNING file=\"My File\" line=\"10\">Test Information: Hello: 55</WARNING>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, log, OOOUnitTestReporter_LogLevel_Error, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Test Information: Hello: 55</ERROR>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCheck(OOOCall(pReporter, check, TRUE, "My File", 10, "TRUE"));
	OOOCheck(OOOCall(pOutputMock, check, NULL));

	OOOCheck(!OOOCall(pReporter, check, FALSE, "My File", 10, "FALSE"));
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Failed check: FALSE</ERROR>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, endTestReport);
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, endReport);
	OOOCheck(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n</REPORT>\nEND_UNIT_TEST_OUTPUT\n"));

	OOODestroy(pReporter);
	OOODestroy(pOutputMock);
}
