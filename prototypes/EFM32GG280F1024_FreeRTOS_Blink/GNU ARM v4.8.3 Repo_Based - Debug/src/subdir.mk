################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EFM32GG280F1024_FreeRTOS_Blink.c \
../src/autogen_init.c \
../src/autogen_lfxo.c 

OBJS += \
./src/EFM32GG280F1024_FreeRTOS_Blink.o \
./src/autogen_init.o \
./src/autogen_lfxo.o 

C_DEPS += \
./src/EFM32GG280F1024_FreeRTOS_Blink.d \
./src/autogen_init.d \
./src/autogen_lfxo.d 


# Each subdirectory must supply rules for building sources it contributes
src/EFM32GG280F1024_FreeRTOS_Blink.o: ../src/EFM32GG280F1024_FreeRTOS_Blink.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/gpiointerrupt/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/nvm/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/rtcdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/spidrv/inc" -I"C:\Users\Brandon\Desktop\Athena\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\Brandon\Desktop\Athena\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\Brandon\Desktop\Athena\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/EFM32GG280F1024_FreeRTOS_Blink.d" -MT"src/EFM32GG280F1024_FreeRTOS_Blink.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_init.o: ../src/autogen_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/gpiointerrupt/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/nvm/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/rtcdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/spidrv/inc" -I"C:\Users\Brandon\Desktop\Athena\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\Brandon\Desktop\Athena\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\Brandon\Desktop\Athena\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_init.d" -MT"src/autogen_init.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/autogen_lfxo.o: ../src/autogen_lfxo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/gpiointerrupt/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/nvm/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/rtcdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emdrv/spidrv/inc" -I"C:\Users\Brandon\Desktop\Athena\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -I"C:\Users\Brandon\Desktop\Athena\lib3rdParty\FreeRTOS/Source/include" -I"C:\Users\Brandon\Desktop\Athena\lib3rdParty\FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/arm-none-eabi/include" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include" -I"C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\gnu_arm\4.8_2013q4\/lib/gcc/arm-none-eabi/4.8.3/include-fixed" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/autogen_lfxo.d" -MT"src/autogen_lfxo.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


