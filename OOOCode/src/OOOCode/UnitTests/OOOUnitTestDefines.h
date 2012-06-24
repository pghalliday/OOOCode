#ifndef OOOUnitTestDefines_H
#define OOOUnitTestDefines_H

#include "OOOIUnitTest.h"

/* Start the implementation of IUnitTest called NAME */
#define OOOTest(NAME) \
	_OOODeclare(NAME, char * szName) \
		OOOImplements \
			OOOImplement(OOOIUnitTest); \
		_OOOImplementsEnd(NAME) \
		OOOExports \
		_OOOExportsEnd(NAME) \
	_OOODeclareEnd(NAME) \
	\
	_OOOPrivateData(NAME) \
		char * szName; \
	_OOOPrivateDataEnd(NAME) \
	\
	_OOODestructor(NAME) \
	_OOODestructorEnd(NAME) \
	\
	static void OOOPaste(NAME, _actuallyRun)(NAME * OOOThis, OOOUnitTestReporter * OOOReporter); \
	_OOOMethod(NAME, void, run, OOOUnitTestReporter * OOOReporter) \
		_OOOPCall(NAME, OOOThis, actuallyRun, OOOReporter); \
	OOOMethodEnd \
	\
	_OOOMethod(NAME, char *, getName) \
		return _OOOField(NAME, OOOThis, szName); \
	OOOMethodEnd \
	\
	_OOOConstructor(NAME, char * szName) \
		_OOOMapVirtuals(OOOIUnitTest) \
			_OOOVirtualMapping(NAME, run), \
			_OOOVirtualMapping(NAME, getName), \
			_OOOVirtualMapping(NAME, destroy) \
		_OOOMapVirtualsEnd(OOOIUnitTest) \
		_OOOField(NAME, OOOThis, szName) = szName; \
	OOOConstructorEnd \
	\
	static void OOOPaste(NAME, _actuallyRun)(NAME * OOOThis, OOOUnitTestReporter * OOOReporter)

#define OOOTestInfo0(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, OOOUnitTestReporter_LogLevel_Information, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOTestInfo1(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, OOOUnitTestReporter_LogLevel_Information, __FILE__, __LINE__, MESSAGE)
#define OOOTestInfo(MESSAGE, ARGS...)	OOOPaste(OOOTestInfo, OOOIsEmpty(ARGS))(MESSAGE, ARGS...)

#define OOOTestWarning0(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, OOOUnitTestReporter_LogLevel_Warning, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOTestWarning1(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, OOOUnitTestReporter_LogLevel_Warning, __FILE__, __LINE__, MESSAGE)
#define OOOTestWarning(MESSAGE, ARGS...)	OOOPaste(OOOTestWarning, OOOIsEmpty(ARGS))(MESSAGE, ARGS...)

#define OOOTestError0(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, OOOUnitTestReporter_LogLevel_Error, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOTestError1(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, OOOUnitTestReporter_LogLevel_Error, __FILE__, __LINE__, MESSAGE)
#define OOOTestError(MESSAGE, ARGS...)	OOOPaste(OOOTestError, OOOIsEmpty(ARGS))(MESSAGE, ARGS...)

#define OOOTestCheck(CONDITION)	(OOOCall(OOOReporter, check, (CONDITION), __FILE__, __LINE__, OOOQuote(CONDITION)))

#endif
