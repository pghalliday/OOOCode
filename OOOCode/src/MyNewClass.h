#ifndef MyNewClass_H
#define MyNewClass_H

#include "OOOCode.h"
#include "MyNewInterface.h"

BEGIN_CLASS(MyNewClass, int nMyField)
	ADD_INTERFACE(MyNewInterface)
END_CLASS

#endif
