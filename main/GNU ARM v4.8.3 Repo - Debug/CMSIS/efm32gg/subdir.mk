################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/efm32gg/system_efm32gg.c 

S_SRCS += \
../CMSIS/efm32gg/startup_gcc_efm32gg.s 

OBJS += \
./CMSIS/efm32gg/startup_gcc_efm32gg.o \
./CMSIS/efm32gg/system_efm32gg.o 

C_DEPS += \
./CMSIS/efm32gg/system_efm32gg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/efm32gg/%.o: ../CMSIS/efm32gg/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -c -x assembler-with-cpp -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/usb/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" '-DEFM32GG280F1024=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32gg/system_efm32gg.o: ../CMSIS/efm32gg/system_efm32gg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/usb/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32gg/system_efm32gg.d" -MT"CMSIS/efm32gg/system_efm32gg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


