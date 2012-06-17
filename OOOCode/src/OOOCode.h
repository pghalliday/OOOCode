#define CLASS(NAME) \
	typedef struct _##NAME NAME;\
	\
	typedef void (* NAME##_destructor)(NAME * pThis); \
	\
	struct _##NAME \
	{ \
		NAME##_destructor cbDestroy; \
	}; \
	\
	static void NAME##_destroy(NAME * pThis) \
	{ \
		O_free(pThis); \
	} \
	\
	static inline NAME * NAME##_construct(void) \
	{ \
		NAME * pThis = O_malloc(sizeof(NAME)); \
		pThis->cbDestroy = NAME##_destroy; \
		return pThis; \
	}

#define CONSTRUCT(NAME) \
	NAME##_construct();

#define DESTROY(INSTANCE) \
	INSTANCE->cbDestroy(INSTANCE); \
	INSTANCE = NULL;

