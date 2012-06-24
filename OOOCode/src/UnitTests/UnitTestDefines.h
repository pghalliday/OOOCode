#ifndef UnitTestDefines_H
#define UnitTestDefines_H

#include "IUnitTest.h"

/* Start the implementation of IUnitTest called NAME */
#define OOOTest(NAME) \
	_OOODeclare(NAME, char * szName) \
		OOOImplements \
			OOOImplement(IUnitTest); \
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
	static void PASTE(NAME, _actuallyRun)(NAME * OOOThis, UnitTestReporter * OOOReporter); \
	_OOOMethod(NAME, void, run, UnitTestReporter * OOOReporter) \
		_OOOPCall(NAME, OOOThis, actuallyRun, OOOReporter); \
	OOOMethodEnd \
	\
	_OOOMethod(NAME, char *, getName) \
		return _OOOField(NAME, OOOThis, szName); \
	OOOMethodEnd \
	\
	_OOOConstructor(NAME, char * szName) \
		_OOOMapVirtuals(IUnitTest) \
			_OOOVirtualMapping(NAME, run), \
			_OOOVirtualMapping(NAME, getName), \
			_OOOVirtualMapping(NAME, destroy) \
		_OOOMapVirtualsEnd(IUnitTest) \
		_OOOField(NAME, OOOThis, szName) = szName; \
	OOOConstructorEnd \
	\
	static void PASTE(NAME, _actuallyRun)(NAME * OOOThis, UnitTestReporter * OOOReporter)

#define OOOTestInfo0(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, UnitTestReporter_LogLevel_Information, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOTestInfo1(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, UnitTestReporter_LogLevel_Information, __FILE__, __LINE__, MESSAGE)
#define OOOTestInfo(MESSAGE, ARGS...)	PASTE(OOOTestInfo, ISEMPTY(ARGS))(MESSAGE, ARGS...)

#define OOOTestWarning0(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, UnitTestReporter_LogLevel_Warning, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOTestWarning1(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, UnitTestReporter_LogLevel_Warning, __FILE__, __LINE__, MESSAGE)
#define OOOTestWarning(MESSAGE, ARGS...)	PASTE(OOOTestWarning, ISEMPTY(ARGS))(MESSAGE, ARGS...)

#define OOOTestError0(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, UnitTestReporter_LogLevel_Error, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOTestError1(MESSAGE, ARGS...)	OOOCall(OOOReporter, log, UnitTestReporter_LogLevel_Error, __FILE__, __LINE__, MESSAGE)
#define OOOTestError(MESSAGE, ARGS...)	PASTE(OOOTestError, ISEMPTY(ARGS))(MESSAGE, ARGS...)

#define OOOTestCheck(CONDITION)	(OOOCall(OOOReporter, check, (CONDITION), __FILE__, __LINE__, QUOTE(CONDITION)))

#endif
