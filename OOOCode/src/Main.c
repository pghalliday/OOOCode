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

/* The old pattern */
#include "MyClass.h"

static void Main_testOriginalPattern(void)
{
	MyClass * pInstance = MyClass_create(5);
	MyInterface * pInterfaceInstance = MyClass_asMyInterface(pInstance);

	/* Method tests */
	assert(MyClass_getMyField(pInstance) == 5);
	assert(MyInterface_myMethod(pInterfaceInstance, 3) == 8);

	MyClass_destroy(pInstance);
}

/* The new pattern */
#include "MyNewClass.class"

static void Main_testNewPattern(void)
{
	MyNewClass * pInstance = NULL;
	pInstance = CONSTRUCT(MyNewClass);
	assert(pInstance);
	DESTROY(pInstance);
	assert(!pInstance);
}

void main(void)
{
	RUN_TEST(Main_testOriginalPattern);
	RUN_TEST(Main_testNewPattern);

	/* Stick around so the VSTB does not exit and we know we ran everything */
	O_debug("OOOCode: Tests passed\n");
	Main_waitToExit();
}
