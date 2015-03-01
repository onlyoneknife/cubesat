################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/efm32gg/subdir.mk
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
all: EFM32GG280F1024_ADC.axf

# Tool invocations
EFM32GG280F1024_ADC.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "EFM32GG280F1024_ADC.ld" -Xlinker --gc-sections -Xlinker -Map="EFM32GG280F1024_ADC.map" --specs=nano.specs -o EFM32GG280F1024_ADC.axf "./src/empty_project.o" "./emlib/em_adc.o" "./emlib/em_cmu.o" "./emlib/em_gpio.o" "./emlib/em_system.o" "./CMSIS/efm32gg/startup_efm32gg.o" "./CMSIS/efm32gg/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: EFM32GG280F1024_ADC.hex'
	arm-none-eabi-objcopy -O ihex "EFM32GG280F1024_ADC.axf" "EFM32GG280F1024_ADC.hex"
	@echo ' '

	@echo 'Building bin file: EFM32GG280F1024_ADC.bin'
	arm-none-eabi-objcopy -O binary "EFM32GG280F1024_ADC.axf" "EFM32GG280F1024_ADC.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "EFM32GG280F1024_ADC.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) EFM32GG280F1024_ADC.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
