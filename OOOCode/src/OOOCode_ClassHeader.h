#ifndef OOOCode_ClassHeader_H
#define OOOCode_ClassHeader_H

#define OOOExportClass(CLASS_NAME, CONSTRUCTOR_ARGS...) \
	typedef struct _##CLASS_NAME CLASS_NAME; \
	extern CLASS_NAME * CLASS_NAME##_construct(CONSTRUCTOR_ARGS); \
	extern void CLASS_NAME##_destroy(CLASS_NAME * pThis);

#define OOOExportCast(CLASS_NAME, INTERFACE_NAME) \
	extern INTERFACE_NAME * CLASS_NAME##_as##INTERFACE_NAME(CLASS_NAME * pThis);

#endif
