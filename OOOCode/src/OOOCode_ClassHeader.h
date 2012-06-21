#ifndef OOOCode_ClassHeader_H
#define OOOCode_ClassHeader_H

/*
 * If you see something strange in here it is probably deliberate!
 * So if you change it make sure you test a lot.
 *
 * NB. Check MacroNotes.txt for guidelines
 */


#define __OOOClass(CLASS_NAME, CONSTRUCTOR_ARGS...) \
	typedef struct _##CLASS_NAME CLASS_NAME; \
	extern CLASS_NAME * CLASS_NAME##_construct(CONSTRUCTOR_ARGS); \
	typedef struct \
	{ \
		void (* destroy)(CLASS_NAME * OOOThis);
#define _OOOClass(CLASS_NAME, CONSTRUCTOR_ARGS...) __OOOClass(CLASS_NAME , ##CONSTRUCTOR_ARGS)
#define OOOClass(CONSTRUCTOR_ARGS...) _OOOClass(OOOClassName , ##CONSTRUCTOR_ARGS)
#define __OOOMethod(RETURN_TYPE, CLASS_NAME, METHOD_NAME, ARGS...) \
	RETURN_TYPE (* METHOD_NAME)(CLASS_NAME * OOOThis , ##ARGS)
#define _OOOMethod(RETURN_TYPE, CLASS_NAME, METHOD_NAME, ARGS...) __OOOMethod(RETURN_TYPE, CLASS_NAME, METHOD_NAME , ##ARGS)
#define OOOMethod(RETURN_TYPE, METHOD_NAME, ARGS...) _OOOMethod(RETURN_TYPE, OOOClassName, METHOD_NAME , ##ARGS)
#define __OOOInterfaces(CLASS_NAME) \
	} \
	CLASS_NAME##_VTable; \
	typedef struct \
	{
#define _OOOInterfaces(CLASS_NAME) __OOOInterfaces(CLASS_NAME)
#define OOOInterfaces _OOOInterfaces(OOOClassName)
#define OOOImplement(INTERFACE_NAME) \
		INTERFACE_NAME t##INTERFACE_NAME
#define __OOOClassEnd(CLASS_NAME) \
	} \
	CLASS_NAME##_Interfaces; \
	typedef struct _##CLASS_NAME##_PrivateData CLASS_NAME##_PrivateData; \
	struct _##CLASS_NAME \
	{ \
		CLASS_NAME##_PrivateData * pPrivateData; \
		CLASS_NAME##_VTable * pVTable; \
		CLASS_NAME##_Interfaces tInterfaces; \
	};
#define _OOOClassEnd(CLASS_NAME) __OOOClassEnd(CLASS_NAME)
#define OOOClassEnd _OOOClassEnd(OOOClassName)

#define __OOOExportConstructor(CLASS_NAME, CONSTRUCTOR_NAME, CONSTRUCTOR_ARGS...) \
	extern CLASS_NAME * CLASS_NAME##_##CONSTRUCTOR_NAME(CONSTRUCTOR_ARGS)
#define _OOOExportConstructor(CLASS_NAME, CONSTRUCTOR_NAME, CONSTRUCTOR_ARGS...) __OOOExportConstructor(CLASS_NAME, CONSTRUCTOR_NAME , ##CONSTRUCTOR_ARGS)
#define OOOExportConstructor(CONSTRUCTOR_NAME, CONSTRUCTOR_ARGS...) _OOOExportConstructor(OOOClassName, CONSTRUCTOR_NAME , ##CONSTRUCTOR_ARGS)

#endif
