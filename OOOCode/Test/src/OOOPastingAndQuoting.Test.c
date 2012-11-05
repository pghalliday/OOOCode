#include "OOOUnitTestDefines.h"
#include "OOOPastingAndQuoting.h"

OOOTest(OOOPastingAndQuoting)
{
	OOOCheck(O_strcmp(OOOQuote(Hello), "Hello") == 0);
#define HELLO Hello
	OOOCheck(O_strcmp(OOOQuote(HELLO), "Hello") == 0);
	OOOCheck(O_strcmp(OOOQuote(OOOPaste(Hello, Goodbye)), "HelloGoodbye") == 0);
#define GOODBYE Goodbye
	OOOCheck(O_strcmp(OOOQuote(OOOPaste(HELLO, GOODBYE)), "HelloGoodbye") == 0);
}
