################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/croutine.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/MemMang/heap_1.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/list.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/queue.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/tasks.c \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/timers.c 

OBJS += \
./FreeRTOS/efm32gg/croutine.o \
./FreeRTOS/efm32gg/heap_1.o \
./FreeRTOS/efm32gg/list.o \
./FreeRTOS/efm32gg/port.o \
./FreeRTOS/efm32gg/queue.o \
./FreeRTOS/efm32gg/tasks.o \
./FreeRTOS/efm32gg/timers.o 

C_DEPS += \
./FreeRTOS/efm32gg/croutine.d \
./FreeRTOS/efm32gg/heap_1.d \
./FreeRTOS/efm32gg/list.d \
./FreeRTOS/efm32gg/port_gcc.d \
./FreeRTOS/efm32gg/queue.d \
./FreeRTOS/efm32gg/tasks.d \
./FreeRTOS/efm32gg/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/efm32gg/croutine.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/croutine.d" -MT"FreeRTOS/efm32gg/croutine.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32gg/heap_1.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/MemMang/heap_1.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/heap_1.d" -MT"FreeRTOS/efm32gg/heap_1.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32gg/list.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/list.d" -MT"FreeRTOS/efm32gg/list.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32gg/port.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/port_gcc.d" -MT"FreeRTOS/efm32gg/port_gcc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32gg/queue.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/queue.d" -MT"FreeRTOS/efm32gg/queue.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32gg/tasks.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/tasks.d" -MT"FreeRTOS/efm32gg/tasks.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32gg/timers.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' '-DDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/drivers" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32GG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/gpiointerrupt/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/common/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/nvm/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/rtcdrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/sleep/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emdrv/spidrv/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:\Users\sdamkjar\workspace\UALBERTA_ATHENA_CUBESATOBC\prototypes\EFM32GG280F1024_FreeRTOS_Blink\FreeRTOS" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32gg/timers.d" -MT"FreeRTOS/efm32gg/timers.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


