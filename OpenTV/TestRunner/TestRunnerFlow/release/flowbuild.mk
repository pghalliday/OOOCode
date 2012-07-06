###############################################
# Automatically generated file. Do not edit.
###############################################

FLWBUILD_OPTIONS= -r 500000 -V  \
    -dir ../../TestRunnerDir/release/TestRunnerDir.dir \
    DIRECTORY -b 0 -e 3600.000 -nopp \
    TestRunner -mv "../../TestRunner/release/TestRunner.otv" -justafter  -e 3600.000 -nopp \
    TestRunnerRes -mv "../../TestRunnerRes/release/TestRunnerRes.res" -justafter  -e 3600.000 -nopp

TestRunnerFlow.flw: ../../TestRunnerDir/release/TestRunnerDir.dir
