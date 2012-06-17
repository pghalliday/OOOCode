#include "opentv.h"
#include "assert.h"

#include "MyClass.h"

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
	/*
	record the current memory available so we
	can detect memory leaks
 	*/
	size_t uMemory = O_heap_available();

	MyClass * pInstance = MyClass_create(5);
	MyInterface * pInterfaceInstance = MyClass_asMyInterface(pInstance);

	/* Method tests */
	assert(MyClass_getMyField(pInstance) == 5);
	assert(MyInterface_myMethod(pInterfaceInstance, 3) == 8);

	/* Memory leak test */
	MyClass_destroy(pInstance);
	assert(O_heap_available() == uMemory);

	/* Stick around so the VSTB does not exit and we know we ran everything */
	O_debug("OOOCode: Tests passed\n");
	Main_waitToExit();
}
