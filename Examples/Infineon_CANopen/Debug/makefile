################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include EEPROM/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/SPI_MASTER/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/GLOBAL_CAN/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include Dave/Generated/CLOCK_XMC4/subdir.mk
-include Dave/Generated/CAN_NODE/subdir.mk
-include Dave/Generated/subdir.mk
-include CANopen/stack/storage/subdir.mk
-include CANopen/stack/extra/subdir.mk
-include CANopen/stack/309/subdir.mk
-include CANopen/stack/305/subdir.mk
-include CANopen/stack/304/subdir.mk
-include CANopen/stack/303/subdir.mk
-include CANopen/stack/301/subdir.mk
-include CANopen/stack/subdir.mk
-include CANopen/hardware/subdir.mk
-include CANopen/driver/subdir.mk
-include CANopen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Infineon_CANopen.hex \

SECONDARY_LIST += \
Infineon_CANopen.lst \

SECONDARY_SIZE += \
Infineon_CANopen.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "Infineon_CANopen.map"

TOOLCHAIN_ROOT=D:/Programs/Infineon/Tools/DAVE IDE/4.5.0.202105191637/eclipse/ARM-GCC-49
PROJECT_LOC=D:/Workspace/Development/my/DAVE/Infineon_CANopen

# All Target
all: Infineon_CANopen.elf secondary-outputs

# Tool invocations
Infineon_CANopen.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "Infineon_CANopen.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
Infineon_CANopen.hex: Infineon_CANopen.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "Infineon_CANopen.elf" "Infineon_CANopen.hex"
	@echo 'Finished building: $@'
	@echo.
Infineon_CANopen.lst: Infineon_CANopen.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "Infineon_CANopen.elf" > "Infineon_CANopen.lst"
	@echo 'Finished building: $@'
	@echo.
Infineon_CANopen.siz: Infineon_CANopen.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "Infineon_CANopen.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) CANopen/CANopenNode.o CANopen/driver/CO_driver_target.o CANopen/driver/CO_storageBlank.o CANopen/driver/OD.o CANopen/driver/log.o CANopen/hardware/CANopenHardware.o CANopen/stack/301/CO_Emergency.o CANopen/stack/301/CO_HBconsumer.o CANopen/stack/301/CO_NMT_Heartbeat.o CANopen/stack/301/CO_ODinterface.o CANopen/stack/301/CO_PDO.o CANopen/stack/301/CO_SDOclient.o CANopen/stack/301/CO_SDOserver.o CANopen/stack/301/CO_SYNC.o CANopen/stack/301/CO_TIME.o CANopen/stack/301/CO_fifo.o CANopen/stack/301/crc16-ccitt.o CANopen/stack/303/CO_LEDs.o CANopen/stack/304/CO_GFC.o CANopen/stack/304/CO_SRDO.o CANopen/stack/305/CO_LSSmaster.o CANopen/stack/305/CO_LSSslave.o CANopen/stack/309/CO_gateway_ascii.o CANopen/stack/CANopen.o CANopen/stack/extra/CO_trace.o CANopen/stack/storage/CO_storage.o CANopen/stack/storage/CO_storageEeprom.o Dave/Generated/CAN_NODE/can_node.o Dave/Generated/CAN_NODE/can_node_conf.o Dave/Generated/CLOCK_XMC4/clock_xmc4.o Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o Dave/Generated/DAVE.o Dave/Generated/DIGITAL_IO/digital_io.o Dave/Generated/DIGITAL_IO/digital_io_conf.o Dave/Generated/GLOBAL_CAN/global_can.o Dave/Generated/GLOBAL_CAN/global_can_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/SPI_MASTER/spi_master.o Dave/Generated/SPI_MASTER/spi_master_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o EEPROM/EEPROM_25Series.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc4_eru.o Libraries/XMCLib/src/xmc4_flash.o Libraries/XMCLib/src/xmc4_gpio.o Libraries/XMCLib/src/xmc4_rtc.o Libraries/XMCLib/src/xmc4_scu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o 
	-$(RM) Libraries/XMCLib/src/xmc_dac.o Libraries/XMCLib/src/xmc_dma.o Libraries/XMCLib/src/xmc_dsd.o Libraries/XMCLib/src/xmc_ebu.o Libraries/XMCLib/src/xmc_ecat.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_eth_mac.o Libraries/XMCLib/src/xmc_eth_phy_dp83848.o Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.o Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.o Libraries/XMCLib/src/xmc_fce.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_hrpwm.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_sdmmc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usbd.o Libraries/XMCLib/src/xmc_usbh.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Startup/startup_XMC4800.o Startup/system_XMC4800.o main.o  Infineon_CANopen.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
