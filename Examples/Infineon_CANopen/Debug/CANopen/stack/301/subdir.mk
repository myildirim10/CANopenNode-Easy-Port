################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopen/stack/301/CO_Emergency.c \
../CANopen/stack/301/CO_HBconsumer.c \
../CANopen/stack/301/CO_NMT_Heartbeat.c \
../CANopen/stack/301/CO_ODinterface.c \
../CANopen/stack/301/CO_PDO.c \
../CANopen/stack/301/CO_SDOclient.c \
../CANopen/stack/301/CO_SDOserver.c \
../CANopen/stack/301/CO_SYNC.c \
../CANopen/stack/301/CO_TIME.c \
../CANopen/stack/301/CO_fifo.c \
../CANopen/stack/301/crc16-ccitt.c 

OBJS += \
./CANopen/stack/301/CO_Emergency.o \
./CANopen/stack/301/CO_HBconsumer.o \
./CANopen/stack/301/CO_NMT_Heartbeat.o \
./CANopen/stack/301/CO_ODinterface.o \
./CANopen/stack/301/CO_PDO.o \
./CANopen/stack/301/CO_SDOclient.o \
./CANopen/stack/301/CO_SDOserver.o \
./CANopen/stack/301/CO_SYNC.o \
./CANopen/stack/301/CO_TIME.o \
./CANopen/stack/301/CO_fifo.o \
./CANopen/stack/301/crc16-ccitt.o 

C_DEPS += \
./CANopen/stack/301/CO_Emergency.d \
./CANopen/stack/301/CO_HBconsumer.d \
./CANopen/stack/301/CO_NMT_Heartbeat.d \
./CANopen/stack/301/CO_ODinterface.d \
./CANopen/stack/301/CO_PDO.d \
./CANopen/stack/301/CO_SDOclient.d \
./CANopen/stack/301/CO_SDOserver.d \
./CANopen/stack/301/CO_SYNC.d \
./CANopen/stack/301/CO_TIME.d \
./CANopen/stack/301/CO_fifo.d \
./CANopen/stack/301/crc16-ccitt.d 


# Each subdirectory must supply rules for building sources it contributes
CANopen/stack/301/%.o: ../CANopen/stack/301/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4800_E196x2048 -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4800_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/CANopen" -I"$(PROJECT_LOC)/CANopen/stack" -I"$(PROJECT_LOC)/CANopen/hardware" -I"$(PROJECT_LOC)/CANopen/driver" -I"$(PROJECT_LOC)/EEPROM" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

