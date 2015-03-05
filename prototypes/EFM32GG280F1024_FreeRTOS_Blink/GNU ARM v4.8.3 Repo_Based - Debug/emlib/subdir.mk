################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_assert.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_burtc.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_cmu.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_emu.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_gpio.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_int.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_rmu.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_rtc.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_system.c 

OBJS += \
./emlib/em_assert.o \
./emlib/em_burtc.o \
./emlib/em_cmu.o \
./emlib/em_emu.o \
./emlib/em_gpio.o \
./emlib/em_int.o \
./emlib/em_rmu.o \
./emlib/em_rtc.o \
./emlib/em_system.o 

C_DEPS += \
./emlib/em_assert.d \
./emlib/em_burtc.d \
./emlib/em_cmu.d \
./emlib/em_emu.d \
./emlib/em_gpio.d \
./emlib/em_int.d \
./emlib/em_rmu.d \
./emlib/em_rtc.d \
./emlib/em_system.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_assert.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_assert.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_assert.d" -MT"emlib/em_assert.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_burtc.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_burtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_burtc.d" -MT"emlib/em_burtc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_cmu.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_cmu.d" -MT"emlib/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_emu.d" -MT"emlib/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_gpio.d" -MT"emlib/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_int.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_int.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_int.d" -MT"emlib/em_int.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_rmu.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_rmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_rmu.d" -MT"emlib/em_rmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_rtc.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_rtc.d" -MT"emlib/em_rtc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_system.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emlib/src/em_system.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_system.d" -MT"emlib/em_system.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


