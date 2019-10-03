################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../app.cfg 

C_SRCS += \
../GPIO.c \
../Init.c \
../LED_DIPSW.c \
../main.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./GPIO.d \
./Init.d \
./LED_DIPSW.d \
./main.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./GPIO.obj \
./Init.obj \
./LED_DIPSW.obj \
./main.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"GPIO.obj" \
"Init.obj" \
"LED_DIPSW.obj" \
"main.obj" 

C_DEPS__QUOTED += \
"GPIO.d" \
"Init.d" \
"LED_DIPSW.d" \
"main.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../GPIO.c" \
"../Init.c" \
"../LED_DIPSW.c" \
"../main.c" 


