################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
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
CANopen/stack/storage/%.o: ../CANopen/stack/storage/%.c CANopen/stack/storage/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"D:/Workspace/Development/my/ST_CanBus/CANopen" -I"D:/Workspace/Development/my/ST_CanBus/CANopen/driver" -I"D:/Workspace/Development/my/ST_CanBus/CANopen/hardware" -I"D:/Workspace/Development/my/ST_CanBus/CANopen/stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopen-2f-stack-2f-storage

clean-CANopen-2f-stack-2f-storage:
	-$(RM) ./CANopen/stack/storage/CO_storage.d ./CANopen/stack/storage/CO_storage.o ./CANopen/stack/storage/CO_storageEeprom.d ./CANopen/stack/storage/CO_storageEeprom.o

.PHONY: clean-CANopen-2f-stack-2f-storage

