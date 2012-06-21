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
#include "MyClass.h"

static void Main_testNewPattern(void)
{
	MyClass * pMyClass = OOOConstruct(MyClass, 5);
	IMyClass * iMyClass = OOOCast(IMyClass, pMyClass);
	IMyInterface * iMyInterface = OOOCast(IMyInterface, pMyClass);

	assert(pMyClass);
	assert(iMyClass);
	assert(iMyInterface);
	assert(OOOCall(pMyClass, getMyField) == 5);
	assert(O_strcmp(OOOInterfaceCall(iMyClass, anotherMethod, "Numbers: %d: %d", -87), "Numbers: -87: 5") == 0);
	assert(OOOInterfaceCall(iMyInterface, myMethod, 3) == 8);
	OOOCall(pMyClass, setMyField, 16);
	assert(OOOCall(pMyClass, getMyField) == 16);
	assert(O_strcmp(OOOInterfaceCall(iMyClass, anotherMethod, "Numbers: %d: %d", -87), "Numbers: -87: 16") == 0);
	assert(OOOInterfaceCall(iMyInterface, myMethod, 3) == 19);

	OOODestroy(pMyClass);
}

void main(void)
{
	RUN_TEST(Main_testNewPattern);

	/* Stick around so the VSTB does not exit and we know we ran everything */
	O_debug("OOOCode: Tests passed\n");
	Main_waitToExit();
}
