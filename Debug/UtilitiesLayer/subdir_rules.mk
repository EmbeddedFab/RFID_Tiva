################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
UtilitiesLayer/EF_SpechialTIMER.obj: ../UtilitiesLayer/EF_SpechialTIMER.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/include" --include_path="C:/TI/TivaWare_C_Series-2.1.0.12573" -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="UtilitiesLayer/EF_SpechialTIMER.pp" --obj_directory="UtilitiesLayer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

UtilitiesLayer/std_types.obj: ../UtilitiesLayer/std_types.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/include" --include_path="C:/TI/TivaWare_C_Series-2.1.0.12573" -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="UtilitiesLayer/std_types.pp" --obj_directory="UtilitiesLayer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


