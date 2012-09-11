################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := "C:/OpenTV/SDKSuiteC2.2/SDK/bin/perl"  "C:/OpenTV/SDKSuiteC2.2/SDK/bin/clean.pl"

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/TestRunnerApplication/subdir.mk
-include src/TestRunnerApplication/Message/subdir.mk
-include src/TestRunnerApplication/Listener/TcpServer/subdir.mk
-include src/TestRunnerApplication/Listener/Sockets/subdir.mk
-include src/TestRunnerApplication/Listener/Sockets/MockSocket/subdir.mk
-include src/TestRunnerApplication/Listener/subdir.mk
-include src/TestRunnerApplication/Listener/Link/subdir.mk
-include src/OOOCode/Utilities/subdir.mk
-include src/OOOCode/UnitTests/Reporter/subdir.mk
-include src/OOOCode/UnitTests/Reporter/Debug/subdir.mk
-include src/OOOCode/UnitTests/subdir.mk
-include src/OOOCode/subdir.mk
-include src/subdir.mk
-include objects.mk

BIGDATA :=1
BIGCODE :=1
define deps_include
-include $(1)
OPENTV_DEPS += $(1)
endef

RCD_OPTIONS += -MMD -MT$@ -MF$*.dxd
RCT_OPTIONS += -MMD -MT$@ -MF$*.dxt
C_OPTIONS += -MMD  -MT$@ -MF$*.d
EXP_OPTIONS = -MMD  -MT$@ -MF$*.dx


VPATH := ../
include $(OPENTV)/kit.mak
RC_FLAGS :=$(RC_FLAGS) -vv -ec
COMPILER_INCLUDES2 +=  -I"../src" -I"../src/OOOCode" -I"../src/OOOCode/UnitTests" -I"../src/OOOCode/UnitTests/Reporter" -I"../src/OOOCode/UnitTests/Reporter/Debug" -I"../src/OOOCode/Utilities" -I"../src/TestRunnerApplication/Listener/Link" -I"../src/TestRunnerApplication/Listener/Sockets" -I"../src/TestRunnerApplication/Listener/Sockets/MockSocket" -I"../src/TestRunnerApplication/Message" -I"../src/TestRunnerApplication/Listener" -I"../src/TestRunnerApplication/Runner" -I"../src/TestRunnerApplication"   -O1 $(WARNINGS)
COMPILE+=${COMPILER_INCLUDES2}
POSTLINK_OPTIONS=stacksize=1024
RC_INCLUDES2 +=  -I"../src" -I"../src/OOOCode" -I"../src/OOOCode/UnitTests" -I"../src/OOOCode/UnitTests/Reporter" -I"../src/OOOCode/UnitTests/Reporter/Debug" -I"../src/OOOCode/Utilities" -I"../src/TestRunnerApplication/Listener/Link" -I"../src/TestRunnerApplication/Listener/Sockets" -I"../src/TestRunnerApplication/Listener/Sockets/MockSocket" -I"../src/TestRunnerApplication/Message" -I"../src/TestRunnerApplication/Listener" -I"../src/TestRunnerApplication/Runner" -I"../src/TestRunnerApplication" 
GCCO_FLAGS +=  -O1 $(WARNINGS)
EXP_OPTIONS +=  -I..
-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
OXTS += \
TestRunner.oxt \

OCDS += \
TestRunner.ocd \

ODBS += \
TestRunner.odb \

OOOS += \
TestRunner.ooo \


# All Target
all: TestRunner.otv

# Tool invocations
TestRunner.ooo: $(OBJS) $(RCOS)
	@echo 'Invoking: object linker'
	$(DO_OOO)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
partclean:
	-$(RM) $(OBJS)$(OCDS)$(RTOS)$(ODBS)$(RDOS)$(OXTS)$(RCDS)$(OTVS)$(RCOS)$(RCTS)$(OOOS) $(FR) $(OPENTV_DEPS) TestRunner.otv
clean:
	-$(RM) -d *
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

%.dxt: %.rct
	$(TITLE)
	$(GCC_OCOD) $(RC_INCLUDES)  $(RC_INCLUDES2)  -x c $(GCCO_FLAGS) $(RCT_OPTIONS) -c $< -o $*.rto

%.dxd: %.rcd
	$(TITLE)
	$(GCC_OCOD) $(RC_INCLUDES) -I../$(dir $<) $(RC_INCLUDES2)  -x c $(GCCO_FLAGS) $(RCD_OPTIONS) -c $< -o $*.rdo

%.dx: %.exp
	$(TITLE)
	$(CC) $(COMPILE) $(BIGEXPORT) $(EXP_OPTIONS) -c -o $*.oxt -D__EXPORT_TABLE -x c $<

%.d: %.c
	$(TITLE)
	$(CC) $(COMPILE) $(C_OPTIONS) -c $< -o $*.o

$(foreach dxd,$(RDOS:.rdo=.dxd),$(eval $(call deps_include,$(dxd))))
$(foreach dxt,$(RTOS:.rto=.dxt),$(eval $(call deps_include,$(dxt))))
$(foreach d,$(OBJS:.o=.d),$(eval $(call deps_include,$(d))))
$(foreach dx,$(OXTS:.oxt=.dx),$(eval $(call deps_include,$(dx))))

