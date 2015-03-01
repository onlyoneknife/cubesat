################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Source/system_efm32gg.c 

S_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Source/GCC/startup_efm32gg.S 

OBJS += \
./CMSIS/efm32gg/startup_efm32gg.o \
./CMSIS/efm32gg/system_efm32gg.o 

C_DEPS += \
./CMSIS/efm32gg/system_efm32gg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/efm32gg/startup_efm32gg.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Source/GCC/startup_efm32gg.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -c -x assembler-with-cpp -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/Device/SiliconLabs/EFM32GG/Include" '-DEFM32GG280F1024=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32gg/system_efm32gg.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Source/system_efm32gg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/arm-none-eabi/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32gg/system_efm32gg.d" -MT"CMSIS/efm32gg/system_efm32gg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


