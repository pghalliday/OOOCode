#ifndef OOOCode_ClassHeader_H
#define OOOCode_ClassHeader_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#define _OOOExportClass(CLASS_NAME, CONSTRUCTOR_ARGS...) \
	typedef struct _##CLASS_NAME CLASS_NAME; \
	extern CLASS_NAME * CLASS_NAME##_construct(CONSTRUCTOR_ARGS); \
	extern void CLASS_NAME##_destroy(CLASS_NAME * pThis)
#define OOOExportClass(CLASS_NAME, CONSTRUCTOR_ARGS...) _OOOExportClass(CLASS_NAME , ##CONSTRUCTOR_ARGS)

#define _OOOExportMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	extern RETURN_TYPE CLASS_NAME##_##METHOD_NAME(CLASS_NAME * OOOThis , ##ARGS)
#define OOOExportMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) _OOOExportMethod(CLASS_NAME, RETURN_TYPE, METHOD_NAME , ##ARGS)

#define _OOOExportCast(CLASS_NAME, INTERFACE_NAME) \
	extern INTERFACE_NAME * CLASS_NAME##_as##INTERFACE_NAME(CLASS_NAME * pThis)
#define OOOExportCast(CLASS_NAME, INTERFACE_NAME) _OOOExportCast(CLASS_NAME, INTERFACE_NAME)

#endif
