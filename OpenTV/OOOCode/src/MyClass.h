#ifndef MYCLASS_H_
#define MYCLASS_H_

#include "OOOCode.h"
#include "IMyClass.h"

#define OOOClass MyClass
OOODeclare(int nMyField)
	OOOImplements
		OOOImplement(IMyClass);
	OOOImplementsEnd
	OOOExports
		OOOExport(int, getMyField);
		OOOExport(MyClass *, copy);
		OOOExport(bool, isEqual, MyClass * pCompare);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
