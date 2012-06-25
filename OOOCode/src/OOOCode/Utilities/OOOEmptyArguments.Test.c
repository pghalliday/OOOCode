#include "OOOUnitTestDefines.h"
#include "OOOEmptyArguments.h"

OOOTest(OOOEmptyArguments)
{
	OOOCheck(OOOIsEmpty() == 1);
	OOOCheck(OOOIsEmpty(hello) == 0);
	OOOCheck(OOOIsEmpty(hello, boo) == 0);

#define TEST_MACRO1(ARGS...) OOOIsEmpty(ARGS)
	OOOCheck(TEST_MACRO1() == 1);
	OOOCheck(TEST_MACRO1(hello) == 0);
	OOOCheck(TEST_MACRO1(hello, boo) == 0);

#define TEST_MACRO2(ARG, ARGS...) OOOIsEmpty(ARGS)
	OOOCheck(TEST_MACRO2(hello) == 1);
	OOOCheck(TEST_MACRO2(hello, boo) == 0);
	OOOCheck(TEST_MACRO2(hello, boo, banana) == 0);
	OOOCheck(TEST_MACRO2(hello, boo, TEST_MACRO1(hello, boo)) == 0);
	OOOCheck(TEST_MACRO2(hello, TEST_MACRO1(hello, boo)) == 0);
}
