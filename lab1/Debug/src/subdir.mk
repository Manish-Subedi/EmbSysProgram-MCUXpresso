################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dice.cpp \
../src/DigitalIOPin.cpp \
../src/SleepMilli.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp \
../src/lab1-ex1.cpp \
../src/lab1-ex2.cpp \
../src/lab1-ex3.cpp 

C_SRCS += \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/Dice.o \
./src/DigitalIOPin.o \
./src/SleepMilli.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/lab1-ex1.o \
./src/lab1-ex2.o \
./src/lab1-ex3.o \
./src/sysinit.o 

CPP_DEPS += \
./src/Dice.d \
./src/DigitalIOPin.d \
./src/SleepMilli.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d \
./src/lab1-ex1.d \
./src/lab1-ex2.d \
./src/lab1-ex3.d 

C_DEPS += \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=gnu++11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\Manish\Documents\MCUXpressoIDE_11.5.0_7232\embSysPro\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Manish\Documents\MCUXpressoIDE_11.5.0_7232\embSysPro\lpc_chip_15xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\Manish\Documents\MCUXpressoIDE_11.5.0_7232\embSysPro\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Manish\Documents\MCUXpressoIDE_11.5.0_7232\embSysPro\lpc_chip_15xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


