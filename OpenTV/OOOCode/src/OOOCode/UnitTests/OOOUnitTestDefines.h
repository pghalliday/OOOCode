#ifndef OOOUnitTestDefines_H
#define OOOUnitTestDefines_H

#include "OOOPastingAndQuoting.h"
#include "OOOEmptyArguments.h"

#include "OOOIUnitTest.h"

/* Start the implementation of IUnitTest called NAME */
#define OOOTest(NAME) \
	_OOODeclare(OOOPaste(OOOUnitTest_,NAME)) \
		OOOImplements \
			OOOImplement(OOOIUnitTest) \
		_OOOImplementsEnd(OOOPaste(OOOUnitTest_,NAME)) \
		_OOOExports(OOOPaste(OOOUnitTest_,NAME)) \
		_OOOExportsEnd(OOOPaste(OOOUnitTest_,NAME)) \
	_OOODeclareEnd(OOOPaste(OOOUnitTest_,NAME)) \
	\
	_OOOPrivateData(OOOPaste(OOOUnitTest_,NAME)) \
	_OOOPrivateDataEnd(OOOPaste(OOOUnitTest_,NAME)) \
	\
	_OOODestructor(OOOPaste(OOOUnitTest_,NAME)) \
	_OOODestructorEnd(OOOPaste(OOOUnitTest_,NAME)) \
	\
	static void OOOPaste(OOOPaste(OOOUnitTest_,NAME), _actuallyRun)(OOOPaste(OOOUnitTest_,NAME) * OOOThis, OOOIReporter * iOOOReporter); \
	_OOOMethod(OOOPaste(OOOUnitTest_,NAME), void, run, OOOIReporter * iOOOReporter) \
		_OOOPCall(OOOPaste(OOOUnitTest_,NAME), OOOThis, actuallyRun, iOOOReporter); \
	OOOMethodEnd \
	\
	_OOOMethod(OOOPaste(OOOUnitTest_,NAME), char *, getName) \
		return OOOQuote(NAME); \
	OOOMethodEnd \
	\
	_OOOConstructor(OOOPaste(OOOUnitTest_,NAME)) \
		_OOOMapVirtuals(OOOPaste(OOOUnitTest_,NAME), OOOIUnitTest) \
			_OOOVirtualMapping(OOOPaste(OOOUnitTest_,NAME), run) \
			_OOOVirtualMapping(OOOPaste(OOOUnitTest_,NAME), getName) \
		_OOOMapVirtualsEnd(OOOIUnitTest) \
		_OOOMapMethods(OOOPaste(OOOUnitTest_,NAME)) \
		OOOMapMethodsEnd \
	OOOConstructorEnd \
	\
	static void OOOPaste(OOOPaste(OOOUnitTest_,NAME), _actuallyRun)(OOOPaste(OOOUnitTest_,NAME) * OOOThis, OOOIReporter * iOOOReporter)

#define OOOInfo0(MESSAGE, ARGS...)	OOOICall(iOOOReporter, log, OOOIReporter_LogLevel_Information, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOInfo1(MESSAGE, ARGS...)	OOOICall(iOOOReporter, log, OOOIReporter_LogLevel_Information, __FILE__, __LINE__, MESSAGE)
#define OOOInfo(MESSAGE, ARGS...)	OOOPaste(OOOInfo, OOOIsEmpty(ARGS))(MESSAGE, ARGS...)

#define OOOWarning0(MESSAGE, ARGS...)	OOOICall(iOOOReporter, log, OOOIReporter_LogLevel_Warning, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOWarning1(MESSAGE, ARGS...)	OOOICall(iOOOReporter, log, OOOIReporter_LogLevel_Warning, __FILE__, __LINE__, MESSAGE)
#define OOOWarning(MESSAGE, ARGS...)	OOOPaste(OOOWarning, OOOIsEmpty(ARGS))(MESSAGE, ARGS...)

#define OOOError0(MESSAGE, ARGS...)	OOOICall(iOOOReporter, log, OOOIReporter_LogLevel_Error, __FILE__, __LINE__, MESSAGE, ARGS)
#define OOOError1(MESSAGE, ARGS...)	OOOICall(iOOOReporter, log, OOOIReporter_LogLevel_Error, __FILE__, __LINE__, MESSAGE)
#define OOOError(MESSAGE, ARGS...)	OOOPaste(OOOError, OOOIsEmpty(ARGS))(MESSAGE, ARGS...)

#define OOOCheck(CONDITION)	(OOOICall(iOOOReporter, check, (CONDITION), __FILE__, __LINE__, OOOQuote(CONDITION)))

#endif
