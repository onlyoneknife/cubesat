################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libDrivers/src/subdir.mk
-include emlib/subdir.mk
-include autogen/subdir.mk
-include CMSIS/GCC/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main.axf

# Tool invocations
main.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "main.ld" -Xlinker --gc-sections -Xlinker -Map="main.map" --specs=nano.specs -o main.axf "./emlib/em_acmp.o" "./emlib/em_adc.o" "./emlib/em_aes.o" "./emlib/em_assert.o" "./emlib/em_burtc.o" "./emlib/em_cmu.o" "./emlib/em_dac.o" "./emlib/em_dbg.o" "./emlib/em_dma.o" "./emlib/em_ebi.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_idac.o" "./emlib/em_int.o" "./emlib/em_lcd.o" "./emlib/em_lesense.o" "./emlib/em_letimer.o" "./emlib/em_leuart.o" "./emlib/em_mpu.o" "./emlib/em_msc.o" "./emlib/em_opamp.o" "./emlib/em_pcnt.o" "./emlib/em_prs.o" "./emlib/em_rmu.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_vcmp.o" "./emlib/em_wdog.o" "./main.o" "./libDrivers/src/codeflash.o" "./libDrivers/src/gyro.o" "./libDrivers/src/tempsense.o" "./autogen/autogen_adc0.o" "./autogen/autogen_hfxo.o" "./autogen/autogen_init.o" "./autogen/autogen_lfxo.o" "./autogen/autogen_usart1.o" "./autogen/autogen_usart2.o" "./CMSIS/system_efm32gg.o" "./CMSIS/GCC/startup_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: main.hex'
	arm-none-eabi-objcopy -O ihex "main.axf" "main.hex"
	@echo ' '

	@echo 'Building bin file: main.bin'
	arm-none-eabi-objcopy -O binary "main.axf" "main.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "main.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) main.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
