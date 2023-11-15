################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../medidor_impedancia/src/cr_startup_lpc175x_6x.c \
../medidor_impedancia/src/main.c \
../medidor_impedancia/src/sysinit.c 

OBJS += \
./medidor_impedancia/src/cr_startup_lpc175x_6x.o \
./medidor_impedancia/src/main.o \
./medidor_impedancia/src/sysinit.o 

C_DEPS += \
./medidor_impedancia/src/cr_startup_lpc175x_6x.d \
./medidor_impedancia/src/main.d \
./medidor_impedancia/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
medidor_impedancia/src/%.o: ../medidor_impedancia/src/%.c medidor_impedancia/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"D:\UTN-FRA\FisicaElectronicaIII\zt5\lpc\LPCworkspace\lpc_chip_175x_6x\inc" -I"D:\UTN-FRA\FisicaElectronicaIII\zt5\lpc\LPCworkspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"D:\UTN-FRA\FisicaElectronicaIII\zt5\lpc\LPCworkspace\medidor_impedancia\freertos\inc" -I"D:\UTN-FRA\FisicaElectronicaIII\zt5\lpc\LPCworkspace\medidor_impedancia\medidor_impedancia\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


