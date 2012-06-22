#ifndef OOOCode_ClassHeader_H
#define OOOCode_ClassHeader_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

/*
 * Declare the type and constructor arguments
 */

#define __OOODeclare(CLASS_NAME, CONSTRUCTOR_ARGS...) \
	typedef struct _##CLASS_NAME CLASS_NAME; \
	extern CLASS_NAME * CLASS_NAME##_construct(CONSTRUCTOR_ARGS);
#define _OOODeclare(CLASS_NAME, CONSTRUCTOR_ARGS...) __OOODeclare(CLASS_NAME , ##CONSTRUCTOR_ARGS)
#define OOODeclare(CONSTRUCTOR_ARGS...) _OOODeclare(OOOClass , ##CONSTRUCTOR_ARGS)

/*
 * Export Interfaces
 */

/* Start the interfaces structure */
#define __OOOImplements(CLASS_NAME) \
	typedef struct \
	{
#define _OOOImplements(CLASS_NAME) __OOOImplements(CLASS_NAME)
#define OOOImplements _OOOImplements(OOOClass)

/* Add an interface */
#define _OOOImplement(INTERFACE_NAME) \
		INTERFACE_NAME t##INTERFACE_NAME
#define OOOImplement(INTERFACE_NAME) _OOOImplement(INTERFACE_NAME)

/* End the interfaces structure and declare the type name */
#define __OOOImplementsEnd(CLASS_NAME) \
	} \
	CLASS_NAME##_Interfaces;
#define _OOOImplementsEnd(CLASS_NAME) __OOOImplementsEnd(CLASS_NAME)
#define OOOImplementsEnd _OOOImplementsEnd(OOOClass)

/*
 * Export methods
 */

/* start the vtable structure */
#define __OOOExports(CLASS_NAME) \
	typedef struct \
	{
#define _OOOExports(CLASS_NAME) __OOOExports(CLASS_NAME)
#define OOOExports _OOOExports(OOOClass)

/* add an exported method */
#define __OOOExport(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(CLASS_NAME * OOOThis , ##ARGS)
#define _OOOExport(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) __OOOExport(CLASS_NAME, RETURN_TYPE, METHOD_NAME , ##ARGS)
#define OOOExport(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOExport(OOOClass, RETURN_TYPE, METHOD_NAME , ##ARGS)

/* end the vtable structure and declare the type name */
#define __OOOExportsEnd(CLASS_NAME) \
	} \
	CLASS_NAME##_VTable;
#define _OOOExportsEnd(CLASS_NAME) __OOOExportsEnd(CLASS_NAME)
#define OOOExportsEnd _OOOExportsEnd(OOOClass)

/*
 * End the class declaration and define the public structure
 */

#define __OOODeclareEnd(CLASS_NAME) \
	typedef struct _##CLASS_NAME##_PrivateData CLASS_NAME##_PrivateData; \
	struct _##CLASS_NAME \
	{ \
		void (* destroy)(CLASS_NAME * OOOThis); \
		CLASS_NAME##_PrivateData * pPrivateData; \
		CLASS_NAME##_VTable * pVTable; \
		CLASS_NAME##_Interfaces tInterfaces; \
	};
#define _OOODeclareEnd(CLASS_NAME) __OOODeclareEnd(CLASS_NAME)
#define OOODeclareEnd _OOODeclareEnd(OOOClass)

#endif
