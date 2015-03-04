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
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -c -x assembler-with-cpp -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" '-DEFM32GG280F1024=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32gg/system_efm32gg.o: ../CMSIS/efm32gg/system_efm32gg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32gg/system_efm32gg.d" -MT"CMSIS/efm32gg/system_efm32gg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


