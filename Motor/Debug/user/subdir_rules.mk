################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
user/%.obj: ../user/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo '正在调用： MSP430 Compiler'
	"D:/CCS1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/Users/Tiam/Desktop/MSP430/Motor/user" --include_path="D:/CCS1040/ccs/ccs_base/msp430/include" --include_path="C:/Users/Tiam/Desktop/MSP430/Motor" --include_path="D:/CCS1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="user/$(basename $(<F)).d_raw" --obj_directory="user" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


