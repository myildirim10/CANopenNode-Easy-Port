################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopen/stack/304/CO_GFC.c \
../CANopen/stack/304/CO_SRDO.c 

OBJS += \
./CANopen/stack/304/CO_GFC.o \
./CANopen/stack/304/CO_SRDO.o 

C_DEPS += \
./CANopen/stack/304/CO_GFC.d \
./CANopen/stack/304/CO_SRDO.d 


# Each subdirectory must supply rules for building sources it contributes
CANopen/stack/304/%.o: ../CANopen/stack/304/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4800_E196x2048 -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4800_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/CANopen" -I"$(PROJECT_LOC)/CANopen/stack" -I"$(PROJECT_LOC)/CANopen/hardware" -I"$(PROJECT_LOC)/CANopen/driver" -I"$(PROJECT_LOC)/EEPROM" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

