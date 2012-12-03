#ifndef OOOCode_ClassHeader_H
#define OOOCode_ClassHeader_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */

#include "OOOPaste.h"
#include "OOOIsEmpty.h"

/*
 * Declare the type and constructor arguments. NB. a constructor is
 * defined as an extern variable to enable dynamic linking of modules
 */
#define OOODeclareStruct(CLASS_NAME) \
	typedef struct _##CLASS_NAME CLASS_NAME;
#define OOODeclareConstructorType0(CLASS_NAME, ARGS...) \
	typedef CLASS_NAME * (* CLASS_NAME##_constructor)(ARGS);
#define OOODeclareConstructorType1(CLASS_NAME) \
	typedef CLASS_NAME * (* CLASS_NAME##_constructor)(void);
#define OOODeclare0OOOPublic(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType0(CLASS_NAME, ARGS) \
	extern CLASS_NAME##_constructor CLASS_NAME##_construct;
#define OOODeclare1OOOPublic(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType1(CLASS_NAME) \
	extern CLASS_NAME##_constructor CLASS_NAME##_construct;
#define OOODeclare0OOOPrivate(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType0(CLASS_NAME, ARGS) \
	static CLASS_NAME * _##CLASS_NAME##_construct(ARGS) GCCO_SAFE_DS; \
	static CLASS_NAME##_constructor CLASS_NAME##_construct = _##CLASS_NAME##_construct;
#define OOODeclare1OOOPrivate(CLASS_NAME, ARGS...) \
	OOODeclareStruct(CLASS_NAME) \
	OOODeclareConstructorType1(CLASS_NAME) \
	static CLASS_NAME * _##CLASS_NAME##_construct(void) GCCO_SAFE_DS; \
	static CLASS_NAME##_constructor CLASS_NAME##_construct = _##CLASS_NAME##_construct;
#define __OOODeclare(SCOPE, CLASS_NAME, ARGS...) OOOPaste(OOOPaste(OOODeclare, OOOIsEmpty(ARGS)), SCOPE)(CLASS_NAME, ARGS)
#define _OOODeclare(CLASS_NAME, ARGS...) __OOODeclare(OOOPublic, CLASS_NAME, ARGS)
#define OOODeclare(ARGS...) _OOODeclare(OOOClass, ARGS)
#define OOODeclarePrivate(ARGS...) __OOODeclare(OOOPrivate, OOOClass, ARGS)

/*
 * Export Interfaces
 */

/* Start the interfaces structure */
#define OOOImplements \
	typedef struct \
	{

/* Add an interface */
#define _OOOImplement(INTERFACE_NAME) \
		INTERFACE_NAME t##INTERFACE_NAME;
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
	{ \
		void (* destroy)(CLASS_NAME * OOOThis);
#define _OOOExports(CLASS_NAME) __OOOExports(CLASS_NAME)
#define OOOExports _OOOExports(OOOClass)

/* add an exported method */
#define _OOOExport0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(CLASS_NAME * OOOThis, ARGS);
#define _OOOExport1(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(CLASS_NAME * OOOThis);
#define _OOOExport(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(_OOOExport, OOOIsEmpty(ARGS))(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOExport(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOExport(OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)

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
	struct _##CLASS_NAME \
	{ \
		CLASS_NAME##_VTable * pVTable; \
		CLASS_NAME##_Interfaces tInterfaces; \
	};
#define _OOODeclareEnd(CLASS_NAME) __OOODeclareEnd(CLASS_NAME)
#define OOODeclareEnd _OOODeclareEnd(OOOClass)

/* forward declare a function to be used in private calls */
#define _OOOPCDeclare0(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE CLASS_NAME##_##METHOD_NAME(CLASS_NAME * OOOThis, ARGS) GCCO_SAFE_DS;
#define _OOOPCDeclare1(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) \
	static RETURN_TYPE CLASS_NAME##_##METHOD_NAME(CLASS_NAME * OOOThis) GCCO_SAFE_DS;
#define _OOOPCDeclare(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS...) OOOPaste(_OOOPCDeclare, OOOIsEmpty(ARGS))(CLASS_NAME, RETURN_TYPE, METHOD_NAME, ARGS)
#define OOOPCDeclare(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOPCDeclare(OOOClass, RETURN_TYPE, METHOD_NAME, ARGS)


#endif
