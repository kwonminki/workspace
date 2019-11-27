################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../app.cfg 

C_SRCS += \
../HWI.c \
../SWI.c \
../main.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./HWI.d \
./SWI.d \
./main.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./HWI.obj \
./SWI.obj \
./main.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"HWI.obj" \
"SWI.obj" \
"main.obj" 

C_DEPS__QUOTED += \
"HWI.d" \
"SWI.d" \
"main.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../HWI.c" \
"../SWI.c" \
"../main.c" 


