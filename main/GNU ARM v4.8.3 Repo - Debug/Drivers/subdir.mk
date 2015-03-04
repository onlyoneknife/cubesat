################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/codeflash.c \
../Drivers/gyro.c \
../Drivers/tempsense.c 

OBJS += \
./Drivers/codeflash.o \
./Drivers/gyro.o \
./Drivers/tempsense.o 

C_DEPS += \
./Drivers/codeflash.d \
./Drivers/gyro.d \
./Drivers/tempsense.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/codeflash.o: ../Drivers/codeflash.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"Drivers/codeflash.d" -MT"Drivers/codeflash.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/gyro.o: ../Drivers/gyro.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"Drivers/gyro.d" -MT"Drivers/gyro.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/tempsense.o: ../Drivers/tempsense.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"Drivers/tempsense.d" -MT"Drivers/tempsense.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


