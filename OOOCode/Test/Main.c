#include "opentv.h"
#include "assert.h"
#include "OOODebugLog.h"
#include "OOOLogReporter.h"
#include "OOOUnitTestsRun.h"

void main(void)
{
	size_t uMemory = O_heap_available();
	OOODebugLog * pDebugLog = OOOConstruct(OOODebugLog);
	OOOLogReporter * pReporter = OOOConstruct(OOOLogReporter, OOOCast(OOOILog, pDebugLog));
	OOOUnitTestsRun(OOOCast(OOOIReporter, pReporter));
	OOODestroy(pReporter);
	OOODestroy(pDebugLog);
	assert(O_heap_available() == uMemory);

	/* Stick around so the VSTB does not exit and we know we ran everything */
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
