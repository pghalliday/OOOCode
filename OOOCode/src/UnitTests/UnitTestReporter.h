#ifndef UnitTestReporter_H
#define UnitTestReporter_H

#include "OOOCode.h"
#include "IOutput.h"

typedef enum
{
	UnitTestReporter_LogLevel_Information,
	UnitTestReporter_LogLevel_Warning,
	UnitTestReporter_LogLevel_Error
}
UnitTestReporter_LogLevel;

#define OOOClass UnitTestReporter
OOODeclare(IOutput * iOutput)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, startReport);
		OOOExport(void, startTestReport, char * szName);
		OOOExport(void, log, UnitTestReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...);
		OOOExport(bool, check, bool bCondition, char * szFile, int nLine, char * szCondition);
		OOOExport(void, endTestReport);
		OOOExport(void, endReport);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
