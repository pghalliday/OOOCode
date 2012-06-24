#include "opentv.h"
#include "assert.h"
#include "UnitTestsRun.h"

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

void main(void)
{
	RUN_TEST(UnitTestsRun);

	/* Stick around so the VSTB does not exit and we know we ran everything */
	Main_waitToExit();
}
