#include "MockLink.h"

#define OOOClass MockLink

OOOPrivateData
	unsigned short uMessageClass;
	unsigned short uMessageType;
	bool bIsOpen;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(o_link_error, open, o_link_type nLinkType, char * szModuleName, char * szLinkOptions, unsigned int uTimeout)
{
	/* post the internal message */
	o_message tMessage;
	tMessage.msg_class = OOOF(uMessageClass);
	tMessage.type = OOOF(uMessageType);
	assert(O_post_message(&tMessage) == GOOD);

	/* return no error */
	return O_LINK_ERR_NO_ERROR;
}
OOOMethodEnd

OOOMethod(bool, doMessage, o_message * pMessage)
{
	bool bHandled = FALSE;
	if (O_msg_class(pMessage) == OOOF(uMessageClass) && O_msg_type(pMessage) == OOOF(uMessageType))
	{
		/* post the link up message */
		o_message tMessage;
		tMessage.msg_class = MSG_CLASS_COMM;
		tMessage.type = MSG_TYPE_LINK_UP;
		tMessage.O_LINK_CONDITION = 0;
		assert(O_post_message(&tMessage) == GOOD);

		/* flag the link as open */
		OOOF(bIsOpen) = TRUE;
	}
	return bHandled;
}
OOOMethodEnd

OOOMethod(bool, isOpen)
{
	return OOOF(bIsOpen);
}
OOOMethodEnd


OOOConstructor(unsigned short uMessageClass, unsigned short uMessageType)
{
#define OOOInterface ILink
	OOOMapVirtuals
		OOOVirtualMapping(open)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMethodMapping(doMessage)
		OOOMethodMapping(isOpen)
	OOOMapMethodsEnd

	OOOF(uMessageClass) = uMessageClass;
	OOOF(uMessageType) = uMessageType;
}
OOOConstructorEnd

#undef OOOClass
