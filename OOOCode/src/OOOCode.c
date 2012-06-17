/*
 * ============================================================================
 *  File        : OOOCode.c
 *  Author      : pghalliday
 *  Version     :
 *  Description : TODO: Add descriptions about this file here
 * ============================================================================
 */
#include "opentv.h"

void main()
{
	O_debug( "Entering main loop\n" );
	
	for (;;)
	{       
		o_message msg;

		O_ui_get_event_wait (&msg);
		O_debug ("Got an event: class %d, type %d.\n", O_msg_class(&msg), O_msg_type(&msg) );

        switch ( O_msg_class ( &msg )) 
        {
            case MSG_CLASS_CONTROL:
                if( O_msg_type(&msg) == MSG_TYPE_QUIT ) 
                {
                    O_debug ("Quitting.\n");
                    O_exit ();
                }
                break;
            case MSG_CLASS_UIMS:
			{
				O_ui_interactive_dispatch( &msg );
				break;
			}
            default:
            	break;
        }
	}
}
