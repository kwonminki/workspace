################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="C:/ti/dsplib_c674x_3_4_0_0/packages" --include_path="C:/ti/quickStartOMAPL1x_rCSL/OMAPL1x/support/includes" --include_path="C:/Users/olleh/workspace_v9/LAB8_A" --include_path="C:/Users/olleh/workspace_v9/LAB8_A/lib" --include_path="C:/ti/bios_6_76_02_02/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --define=c6748 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2131422225:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-2131422225-inproc

build-2131422225-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs901/xdctools_3_55_00_11_core/xs" --xdcpath="C:/ti/bios_6_76_02_02/packages;C:/ti/bios_6_76_02_02/packages/myBoard;C:/ti/dsplib_c674x_3_4_0_0/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p myBoard -r release -c "C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-2131422225 ../app.cfg
configPkg/compiler.opt: build-2131422225
configPkg/: build-2131422225


