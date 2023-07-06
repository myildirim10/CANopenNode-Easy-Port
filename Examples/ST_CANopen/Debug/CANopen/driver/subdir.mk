################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopen/driver/CO_driver_blank.c \
../CANopen/driver/CO_storageBlank.c \
../CANopen/driver/OD.c \
../CANopen/driver/log.c 

OBJS += \
./CANopen/driver/CO_driver_blank.o \
./CANopen/driver/CO_storageBlank.o \
./CANopen/driver/OD.o \
./CANopen/driver/log.o 

C_DEPS += \
./CANopen/driver/CO_driver_blank.d \
./CANopen/driver/CO_storageBlank.d \
./CANopen/driver/OD.d \
./CANopen/driver/log.d 


# Each subdirectory must supply rules for building sources it contributes
CANopen/driver/%.o: ../CANopen/driver/%.c CANopen/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"D:/Workspace/Development/my/ST_CanBus/CANopen" -I"D:/Workspace/Development/my/ST_CanBus/CANopen/driver" -I"D:/Workspace/Development/my/ST_CanBus/CANopen/hardware" -I"D:/Workspace/Development/my/ST_CanBus/CANopen/stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopen-2f-driver

clean-CANopen-2f-driver:
	-$(RM) ./CANopen/driver/CO_driver_blank.d ./CANopen/driver/CO_driver_blank.o ./CANopen/driver/CO_storageBlank.d ./CANopen/driver/CO_storageBlank.o ./CANopen/driver/OD.d ./CANopen/driver/OD.o ./CANopen/driver/log.d ./CANopen/driver/log.o

.PHONY: clean-CANopen-2f-driver

