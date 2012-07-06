###############################################
# Automatically generated file. Do not edit.
###############################################

DIRBUILD_OPTIONS= -n OOOCodeDir -i 1000 -v  \
    "../../OOOCode/release/OOOCode.otv" -mn OOOCode -mt autoexec \
    "../../OOOCodeRes/release/OOOCodeRes.res" -mn OOOCodeRes -mt resource

OOOCodeDir.dir: ../../OOOCode/release/OOOCode.otv ../../OOOCodeRes/release/OOOCodeRes.res 
	"$(OPENTV_EXEC)dirbuild" $(DIRBUILD_OPTIONS) -o "OOOCodeDir.dir"

FR="OOOCodeDir.dir" 

