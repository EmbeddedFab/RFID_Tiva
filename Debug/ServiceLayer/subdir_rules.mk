################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ServiceLayer/EF_LcdMenus.obj: ../ServiceLayer/EF_LcdMenus.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/include" --include_path="C:/TI/TivaWare_C_Series-2.1.0.12573" -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ServiceLayer/EF_LcdMenus.pp" --obj_directory="ServiceLayer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ServiceLayer/EF_RFID.obj: ../ServiceLayer/EF_RFID.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/include" --include_path="C:/TI/TivaWare_C_Series-2.1.0.12573" -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ServiceLayer/EF_RFID.pp" --obj_directory="ServiceLayer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ServiceLayer/EF_UserInterface.obj: ../ServiceLayer/EF_UserInterface.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.3/include" --include_path="C:/TI/TivaWare_C_Series-2.1.0.12573" -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ServiceLayer/EF_UserInterface.pp" --obj_directory="ServiceLayer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


