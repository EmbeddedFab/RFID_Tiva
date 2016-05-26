################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./uartstdio.obj" \
"./ServiceLayer/std_types.obj" \
"./MCAL/EF_SpechialTIMER.obj" \
"./MCAL/EF_TIVA_DIO.obj" \
"./MCAL/EF_TIVA_SPI.obj" \
"./MCAL/EF_TIVA_Timer.obj" \
"./MCAL/EF_TIVA_uart.obj" \
"./HAL/EF_RFID.obj" \
"C:/TI/TivaWare_C_Series-2.1.0.12573/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pz.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ServiceLayer/subdir_vars.mk
-include RFID_Reference/Mifare_stk_programGUI/serialtemplate/obj/Debug/subdir_vars.mk
-include RFID_Reference/Mifare_stk_programGUI/serialtemplate/bin/Debug/subdir_vars.mk
-include RFID_Reference/Mifare_stk_programGUI/subdir_vars.mk
-include MCAL/subdir_vars.mk
-include HAL/subdir_vars.mk
-include subdir_rules.mk
-include ServiceLayer/subdir_rules.mk
-include RFID_Reference/Mifare_stk_programGUI/serialtemplate/obj/Debug/subdir_rules.mk
-include RFID_Reference/Mifare_stk_programGUI/serialtemplate/bin/Debug/subdir_rules.mk
-include RFID_Reference/Mifare_stk_programGUI/subdir_rules.mk
-include MCAL/subdir_rules.mk
-include HAL/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RFID_Tiva.out \

EXE_OUTPUTS__QUOTED += \
"RFID_Tiva.out" \

BIN_OUTPUTS += \
RFID_Tiva.hex \

BIN_OUTPUTS__QUOTED += \
"RFID_Tiva.hex" \


# All Target
all: RFID_Tiva.out

# Tool invocations
RFID_Tiva.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off -z -m"RFID_Tiva.map" --heap_size=0 --stack_size=512 -i"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/lib" -i"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="RFID_Tiva_linkInfo.xml" --rom_model -o "RFID_Tiva.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

RFID_Tiva.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armhex"  -o "RFID_Tiva.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "tm4c123gh6pm_startup_ccs.pp" "uartstdio.pp" "ServiceLayer\std_types.pp" "MCAL\EF_SpechialTIMER.pp" "MCAL\EF_TIVA_DIO.pp" "MCAL\EF_TIVA_SPI.pp" "MCAL\EF_TIVA_Timer.pp" "MCAL\EF_TIVA_uart.pp" "HAL\EF_RFID.pp" 
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "uartstdio.obj" "ServiceLayer\std_types.obj" "MCAL\EF_SpechialTIMER.obj" "MCAL\EF_TIVA_DIO.obj" "MCAL\EF_TIVA_SPI.obj" "MCAL\EF_TIVA_Timer.obj" "MCAL\EF_TIVA_uart.obj" "HAL\EF_RFID.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

