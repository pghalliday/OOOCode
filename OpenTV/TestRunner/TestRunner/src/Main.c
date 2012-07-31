#include "opentv.h"
#include "assert.h"
#include "OOODebug.h"
#include "OOODebugReporter.h"
#include "OOOUnitTestsRun.h"

#include "TestRunnerApplication.h"

void main(void)
{
	/* run the tests first */
	OOODebug * pDebug = OOOConstruct(OOODebug);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOIDebug, pDebug));
	OOOUnitTestsRun(OOOCast(OOOIReporter, pReporter));
	OOODestroy(pReporter);
	OOODestroy(pDebug);

	/* Start the application */
	{
		size_t uMemory = O_heap_available();
		OOODestroy(OOOConstruct(TestRunnerApplication));
		O_debug("Memory leaked: %d bytes\n", uMemory - O_heap_available());
		assert(O_heap_available() == uMemory);
	}
}
