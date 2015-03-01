################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EFM32GG280F1024_FreeRTOS_Blink.c \
../src/autogen_init.c \
../src/autogen_lfxo.c \
../src/low_power_tick_management.c 

OBJS += \
./src/EFM32GG280F1024_FreeRTOS_Blink.o \
./src/autogen_init.o \
./src/autogen_lfxo.o \
./src/low_power_tick_management.o 

C_DEPS += \
./src/EFM32GG280F1024_FreeRTOS_Blink.d \
./src/autogen_init.d \
./src/autogen_lfxo.d \
./src/low_power_tick_management.d 


# Each subdirectory must supply rules for building sources it contributes
src/EFM32GG280F1024_FreeRTOS_Blink.o: ../src/EFM32GG280F1024_FreeRTOS_Blink.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/arm-none-eabi/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/EFM32GG280F1024_FreeRTOS_Blink.d" -MT"src/EFM32GG280F1024_FreeRTOS_Blink.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_init.o: ../src/autogen_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/arm-none-eabi/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_init.d" -MT"src/autogen_init.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_lfxo.o: ../src/autogen_lfxo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/arm-none-eabi/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_lfxo.d" -MT"src/autogen_lfxo.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/low_power_tick_management.o: ../src/low_power_tick_management.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/gpiointerrupt/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/config" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/common/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/nvm/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/rtcdrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/sleep/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/arm-none-eabi/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\GNU_ARM/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/drivers" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/kits/common/bsp" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/CMSIS/Include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/emlib/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\SiliconLabs\EFM32/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/low_power_tick_management.d" -MT"src/low_power_tick_management.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


