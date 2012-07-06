###############################################
# Automatically generated file. Do not edit.
###############################################

DIRBUILD_OPTIONS= -n TestRunnerDir -i 1000 -v  \
    "../../TestRunner/release/TestRunner.otv" -mn TestRunner -mt autoexec \
    "../../TestRunnerRes/release/TestRunnerRes.res" -mn TestRunnerRes -mt resource

TestRunnerDir.dir: ../../TestRunner/release/TestRunner.otv ../../TestRunnerRes/release/TestRunnerRes.res 
	"$(OPENTV_EXEC)dirbuild" $(DIRBUILD_OPTIONS) -o "TestRunnerDir.dir"

FR="TestRunnerDir.dir" 

