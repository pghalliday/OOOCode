################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := "C:/OpenTV/SDKSuiteC2.2/SDK/bin/perl"  "C:/OpenTV/SDKSuiteC2.2/SDK/bin/clean.pl"

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk


VPATH := ../
include $(OPENTV)/kit.mak
RC_FLAGS :=$(RC_FLAGS) -vv -ec
-include ../makefile.defs
-include flowbuild.mk

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: OOOCodeFlow.flw

# Tool invocations
OOOCodeFlow.flw: $(OPT_SRCS)
	@echo 'Building target: $@'
	@echo 'Invoking: flowbuilder'
	"$(OPENTV)/bin/flwbuild" $(FLWBUILD_OPTIONS) -o $@
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
partclean:
	-$(RM) $(FLW) $(FR) $(OPENTV_DEPS) OOOCodeFlow.flw
clean:
	-$(RM) -d *
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
