/* Need to include the interface header */
#include "MyInterface.h"

typedef struct _MyClass MyClass;

extern MyClass * MyClass_create(int nMyField);
extern void MyClass_destroy(MyClass * pThis);

extern int MyClass_getMyField(MyClass * pThis);

/* New method to "cast" MyClass to MyInterface */
extern MyInterface * MyClass_asMyInterface(MyClass * pThis);
