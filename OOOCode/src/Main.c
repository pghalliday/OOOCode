#include "opentv.h"
#include "assert.h"
#include "OOOUnitTestsRun.h"

void main(void)
{
	size_t uMemory = O_heap_available();
	OOOUnitTestsRun();
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
