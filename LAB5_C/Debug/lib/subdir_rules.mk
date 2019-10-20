################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lib/%.obj: ../lib/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="C:/ti/quickStartOMAPL1x_rCSL/OMAPL1x/support/includes" --include_path="D:/workspace_v9/LAB5_C" --include_path="D:/workspace_v9/LAB5_C/lib" --include_path="C:/ti/bios_6_76_02_02/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --define=c6748 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="lib/$(basename $(<F)).d_raw" --obj_directory="lib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


