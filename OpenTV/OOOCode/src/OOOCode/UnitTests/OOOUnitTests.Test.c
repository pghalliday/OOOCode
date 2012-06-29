#include "OOOUnitTestDefines.h"

#include "OOOMockDebug.h"
#include "OOODebugReporter.h"
#include "OOOUnitTests.h"

#define OOOClass ReportTest

OOODeclare()
	OOOImplements
		OOOImplement(OOOIUnitTest)
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

OOOMethod(void, run, OOOIReporter * iReporter)
{
	OOOICall(iReporter, log, OOOIReporter_LogLevel_Information, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOICall(iReporter, log, OOOIReporter_LogLevel_Warning, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOICall(iReporter, log, OOOIReporter_LogLevel_Error, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOICall(iReporter, check, TRUE, "My File", 10, "TRUE");
	OOOICall(iReporter, check, FALSE, "My File", 10, "FALSE");
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "My Test";
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIUnitTest
	OOOMapVirtuals
		OOOVirtualMapping(run)
		OOOVirtualMapping(getName)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass

#define OOOClass MemoryLeakTest

OOODeclare()
	OOOImplements
		OOOImplement(OOOIUnitTest)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	void * pMemoryLeak;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOF(pMemoryLeak))
	{
		O_free(OOOF(pMemoryLeak));
	}
}
OOODestructorEnd

OOOMethod(void, run, OOOIReporter * iReporter)
{
	OOOF(pMemoryLeak) = O_malloc(10000);
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "My Test";
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIUnitTest
	OOOMapVirtuals
		OOOVirtualMapping(run)
		OOOVirtualMapping(getName)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass

#define OOOClass MemoryMagicTest

OOODeclare(void * szMemoryMagic)
	OOOImplements
		OOOImplement(OOOIUnitTest)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	void * pMemoryMagic;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, run, OOOIReporter * iReporter)
{
	O_free(OOOF(pMemoryMagic));
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "My Test";
}
OOOMethodEnd

OOOConstructor(void * pMemoryMagic)
{
	#define OOOInterface OOOIUnitTest
	OOOMapVirtuals
		OOOVirtualMapping(run)
		OOOVirtualMapping(getName)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(pMemoryMagic) = pMemoryMagic;
}
OOOConstructorEnd

#undef OOOClass

OOOTest(OOOUnitTests)
{
	OOOMockDebug * pMockDebug = OOOConstruct(OOOMockDebug);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOIDebug, pMockDebug));
	ReportTest * pReportTest = OOOConstruct(ReportTest);
	MemoryLeakTest * pMemoryLeakTest = OOOConstruct(MemoryLeakTest);
	void * pMemoryMagic = O_malloc(10000);
	MemoryMagicTest * pMemoryMagicTest = OOOConstruct(MemoryMagicTest, pMemoryMagic);
	OOOIUnitTest * aTests[] =
	{
		OOOCast(OOOIUnitTest, pReportTest),
		OOOCast(OOOIUnitTest, pMemoryLeakTest),
		OOOCast(OOOIUnitTest, pMemoryMagicTest),
		NULL
	};
	OOOUnitTests * pTests = OOOConstruct(OOOUnitTests, OOOCast(OOOIReporter, pReporter), aTests);

	OOOCall(pTests, run);

	assert(OOOCall(pMockDebug, check,
			"BEGIN_UNIT_TEST_OUTPUT\n<?xml version \"1.0\"?><REPORT>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<INFORMATION file=\"My File\" line=\"10\">Test Information: Hello: 55</INFORMATION>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<WARNING file=\"My File\" line=\"10\">Test Information: Hello: 55</WARNING>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Test Information: Hello: 55</ERROR>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Failed check: FALSE</ERROR>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<MEMORY_LEAK test=\"My Test\" bytes=\"%u\"/>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<MEMORY_LEAK test=\"My Test\" bytes=\"10004\"/>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<MEMORY_MAGIC test=\"My Test\" bytes=\"10004\"/>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</REPORT>\nEND_UNIT_TEST_OUTPUT\n",
			/* Memory lost in OutputMock while running the test (will be recovered after check method exits) */
			O_strlen(
					"BEGIN_UNIT_TEST_OUTPUT\n<INFORMATION file=\"My File\" line=\"10\">Test Information: Hello: 55</INFORMATION>\nEND_UNIT_TEST_OUTPUT\n"
					"BEGIN_UNIT_TEST_OUTPUT\n<WARNING file=\"My File\" line=\"10\">Test Information: Hello: 55</WARNING>\nEND_UNIT_TEST_OUTPUT\n"
					"BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Test Information: Hello: 55</ERROR>\nEND_UNIT_TEST_OUTPUT\n"
					"BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Failed check: FALSE</ERROR>\nEND_UNIT_TEST_OUTPUT\n"
					)
			));

	OOODestroy(pTests);
	OOODestroy(pReportTest);
	OOODestroy(pMemoryLeakTest);
	OOODestroy(pMemoryMagicTest);
	OOODestroy(pReporter);
	OOODestroy(pMockDebug);
}
