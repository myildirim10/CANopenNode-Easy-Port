################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopen/stack/storage/CO_storage.c \
../CANopen/stack/storage/CO_storageEeprom.c 

OBJS += \
./CANopen/stack/storage/CO_storage.o \
./CANopen/stack/storage/CO_storageEeprom.o 

C_DEPS += \
./CANopen/stack/storage/CO_storage.d \
./CANopen/stack/storage/CO_storageEeprom.d 


# Each subdirectory must supply rules for building sources it contributes
CANopen/stack/storage/%.o: ../CANopen/stack/storage/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4800_E196x2048 -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4800_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/CANopen" -I"$(PROJECT_LOC)/CANopen/stack" -I"$(PROJECT_LOC)/CANopen/hardware" -I"$(PROJECT_LOC)/CANopen/driver" -I"$(PROJECT_LOC)/EEPROM" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

