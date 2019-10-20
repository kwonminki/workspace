################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6740 --include_path="C:/ti/quickStartOMAPL1x_rCSL/OMAPL1x/support/includes" --include_path="D:/workspace_v9/LAB5_A" --include_path="D:/workspace_v9/LAB5_A/lib" --include_path="C:/ti/bios_6_76_02_02/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --define=c6748 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2129715489:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-2129715489-inproc

build-2129715489-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs901/xdctools_3_55_00_11_core/xs" --xdcpath="C:/ti/bios_6_76_02_02/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p ti.platforms.evm6748 -r release -c "C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-2129715489 ../app.cfg
configPkg/compiler.opt: build-2129715489
configPkg/: build-2129715489


