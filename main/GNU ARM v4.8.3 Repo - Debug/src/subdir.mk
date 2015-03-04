################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_adc0.c \
C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_hfxo.c \
C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_init.c \
C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_lfxo.c \
C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_usart1.c \
C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_usart2.c 

OBJS += \
./src/autogen_adc0.o \
./src/autogen_hfxo.o \
./src/autogen_init.o \
./src/autogen_lfxo.o \
./src/autogen_usart1.o \
./src/autogen_usart2.o 

C_DEPS += \
./src/autogen_adc0.d \
./src/autogen_hfxo.d \
./src/autogen_init.d \
./src/autogen_lfxo.d \
./src/autogen_usart1.d \
./src/autogen_usart2.d 


# Each subdirectory must supply rules for building sources it contributes
src/autogen_adc0.o: C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_adc0.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_adc0.d" -MT"src/autogen_adc0.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_hfxo.o: C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_hfxo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_hfxo.d" -MT"src/autogen_hfxo.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_init.o: C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_init.d" -MT"src/autogen_init.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_lfxo.o: C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_lfxo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_lfxo.d" -MT"src/autogen_lfxo.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_usart1.o: C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_usart1.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_usart1.d" -MT"src/autogen_usart1.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_usart2.o: C:/Users/sdamkjar/workspace/UALBERTA_ATHENA_CUBESATOBC/libAutogen/src/autogen_usart2.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/FreeRTOS//Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/usb/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/Device/SiliconLabs/EFM32GG/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC/lib3rdParty/SiliconLabs/EFM32/CMSIS/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_usart2.d" -MT"src/autogen_usart2.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


