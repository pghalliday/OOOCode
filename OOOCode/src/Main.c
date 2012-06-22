#include "opentv.h"
#include "assert.h"


/* Test running and memory checking code */
static size_t Main_uMemory;
static void Main_recordMemory(void)
{
	Main_uMemory = O_heap_available();
}
static void Main_checkMemory(void)
{
	assert(O_heap_available() == Main_uMemory);
}
#define RUN_TEST(TEST) {Main_recordMemory(); TEST(); Main_checkMemory();}

/* This method just waits for a quit message and then exits the application */
static void Main_waitToExit(void)
{
	while (TRUE)
	{
		o_message tMessage;
		O_ui_get_event_wait(&tMessage);
		if (O_msg_class(&tMessage) == MSG_CLASS_CONTROL)
		{
			if (O_msg_type(&tMessage) == MSG_TYPE_QUIT)
			{
				O_exit();
			}
		}
	}
}

/* The new pattern */
#include "OutputMock.h"
#include "UnitTests.h"

static void Main_testUnitTestReporter(void)
{
	OutputMock * pOutputMock = OOOConstruct(OutputMock);
	UnitTestReporter * pReporter = OOOConstruct(UnitTestReporter, OOOCast(IOutput, pOutputMock));

	OOOCall(pReporter, startReport);
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<?xml version \"1.0\"?><REPORT>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, startTestReport, "My Test");
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, log, UnitTestReporter_LogLevel_Information, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<INFORMATION file=\"My File\" line=\"10\">Test Information: Hello: 55</INFORMATION>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, log, UnitTestReporter_LogLevel_Warning, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<WARNING file=\"My File\" line=\"10\">Test Information: Hello: 55</WARNING>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, log, UnitTestReporter_LogLevel_Error, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Test Information: Hello: 55</ERROR>\nEND_UNIT_TEST_OUTPUT\n"));

	assert(OOOCall(pReporter, check, TRUE, "My File", 10, "TRUE"));
	assert(OOOCall(pOutputMock, check, NULL));

	assert(!OOOCall(pReporter, check, FALSE, "My File", 10, "FALSE"));
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Failed check: FALSE</ERROR>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, endTestReport);
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCall(pReporter, endReport);
	assert(OOOCall(pOutputMock, check, "BEGIN_UNIT_TEST_OUTPUT\n</REPORT>\nEND_UNIT_TEST_OUTPUT\n"));

	OOODestroy(pReporter);
	OOODestroy(pOutputMock);
}

#define OOOClass MyUnitTest

OOODeclare()
	OOOImplements
		OOOImplement(IUnitTest);
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, run, UnitTestReporter * pReporter);
{
	OOOCall(pReporter, log, UnitTestReporter_LogLevel_Information, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCall(pReporter, log, UnitTestReporter_LogLevel_Warning, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCall(pReporter, log, UnitTestReporter_LogLevel_Error, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCall(pReporter, check, TRUE, "My File", 10, "TRUE");
	OOOCall(pReporter, check, FALSE, "My File", 10, "FALSE");
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface IUnitTest
	OOOMapVirtuals
		OOOVirtualMapping(run)
	OOOMapVirtualsEnd
	#undef OOOInterface
}
OOOConstructorEnd

#undef OOOClass

static void Main_testUnitTests(void)
{
	OutputMock * pOutputMock = OOOConstruct(OutputMock);
	UnitTestReporter * pReporter = OOOConstruct(UnitTestReporter, OOOCast(IOutput, pOutputMock));
	MyUnitTest * pTest = OOOConstruct(MyUnitTest);
	UnitTests * pTests = OOOConstruct(UnitTests, pReporter);

	OOOCall(pTests, addTest, "My Test", OOOCast(IUnitTest, pTest));
	OOOCall(pTests, runAll);
	assert(OOOCall(pOutputMock, check,
			"BEGIN_UNIT_TEST_OUTPUT\n<?xml version \"1.0\"?><REPORT>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<INFORMATION file=\"My File\" line=\"10\">Test Information: Hello: 55</INFORMATION>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<WARNING file=\"My File\" line=\"10\">Test Information: Hello: 55</WARNING>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Test Information: Hello: 55</ERROR>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Failed check: FALSE</ERROR>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</REPORT>\nEND_UNIT_TEST_OUTPUT\n"
			));

	OOODestroy(pTests);
	OOODestroy(pTest);
	OOODestroy(pReporter);
	OOODestroy(pOutputMock);
}

void main(void)
{
	RUN_TEST(Main_testUnitTestReporter);
	RUN_TEST(Main_testUnitTests);
	O_debug("OOOCode: Tests passed\n");

	/* Stick around so the VSTB does not exit and we know we ran everything */
	Main_waitToExit();
}
