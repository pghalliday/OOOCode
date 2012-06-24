#ifndef OOOUnitTestReporter_H
#define OOOUnitTestReporter_H

#include "OOOCode.h"
#include "OOOIOutput.h"

typedef enum
{
	OOOUnitTestReporter_LogLevel_Information,
	OOOUnitTestReporter_LogLevel_Warning,
	OOOUnitTestReporter_LogLevel_Error
}
OOOUnitTestReporter_LogLevel;

#define OOOClass OOOUnitTestReporter
OOODeclare(OOOIOutput * iOutput)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, startReport);
		OOOExport(void, startTestReport, char * szName);
		OOOExport(void, log, OOOUnitTestReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...);
		OOOExport(bool, check, bool bCondition, char * szFile, int nLine, char * szCondition);
		OOOExport(void, memoryLeak, char * szTest, size_t uBytesLost);
		OOOExport(void, memoryMagic, char * szTest, size_t uBytesGained);
		OOOExport(void, endTestReport);
		OOOExport(void, endReport);
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
