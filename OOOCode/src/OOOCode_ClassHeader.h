#ifndef OOOCode_ClassHeader_H
#define OOOCode_ClassHeader_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#define __OOOImplements(CLASS_NAME) \
	typedef struct \
	{
#define _OOOImplements(CLASS_NAME) __OOOImplements(CLASS_NAME)
#define OOOImplements _OOOImplements(OOOClass)
#define OOOImplement(INTERFACE_NAME) \
		INTERFACE_NAME t##INTERFACE_NAME
#define __OOOImplementsEnd(CLASS_NAME) \
	} \
	CLASS_NAME##_Interfaces;
#define _OOOImplementsEnd(CLASS_NAME) __OOOImplementsEnd(CLASS_NAME)
#define OOOImplementsEnd _OOOImplementsEnd(OOOClass)

#define __OOOExports(CLASS_NAME) \
	typedef struct \
	{
#define _OOOExports(CLASS_NAME) __OOOExports(CLASS_NAME)
#define OOOExports _OOOExports(OOOClass)
#define OOOExport(RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(void * OOOThis , ##ARGS)
#define __OOOExportsEnd(CLASS_NAME) \
	} \
	CLASS_NAME##_VTable;
#define _OOOExportsEnd(CLASS_NAME) __OOOExportsEnd(CLASS_NAME)
#define OOOExportsEnd _OOOExportsEnd(OOOClass)

#define __OOOExportConstructor(CLASS_NAME, CONSTRUCTOR_ARGS...) \
	typedef struct _##CLASS_NAME CLASS_NAME; \
	typedef struct _##CLASS_NAME##_PrivateData CLASS_NAME##_PrivateData; \
	struct _##CLASS_NAME \
	{ \
		void (* destroy)(CLASS_NAME * OOOThis); \
		CLASS_NAME##_PrivateData * pPrivateData; \
		CLASS_NAME##_VTable * pVTable; \
		CLASS_NAME##_Interfaces tInterfaces; \
	}; \
	extern CLASS_NAME * CLASS_NAME##_construct(CONSTRUCTOR_ARGS);
#define _OOOExportConstructor(CLASS_NAME, CONSTRUCTOR_ARGS...) __OOOExportConstructor(CLASS_NAME , ##CONSTRUCTOR_ARGS)
#define OOOExportConstructor(CONSTRUCTOR_ARGS...) _OOOExportConstructor(OOOClass , ##CONSTRUCTOR_ARGS)

#endif
