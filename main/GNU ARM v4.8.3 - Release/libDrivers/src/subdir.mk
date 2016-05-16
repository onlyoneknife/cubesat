################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/codeflash.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/dmactrl.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/fatfs.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/fram.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/gyro.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/i2c.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/low_power_tick_management.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/mag.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/microsd.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/rtc.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/sleep.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/spi.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/tempsense.c 

OBJS += \
./libDrivers/src/codeflash.o \
./libDrivers/src/dmactrl.o \
./libDrivers/src/fatfs.o \
./libDrivers/src/fram.o \
./libDrivers/src/gyro.o \
./libDrivers/src/i2c.o \
./libDrivers/src/low_power_tick_management.o \
./libDrivers/src/mag.o \
./libDrivers/src/microsd.o \
./libDrivers/src/rtc.o \
./libDrivers/src/sleep.o \
./libDrivers/src/spi.o \
./libDrivers/src/tempsense.o 

C_DEPS += \
./libDrivers/src/codeflash.d \
./libDrivers/src/dmactrl.d \
./libDrivers/src/fatfs.d \
./libDrivers/src/fram.d \
./libDrivers/src/gyro.d \
./libDrivers/src/i2c.d \
./libDrivers/src/low_power_tick_management.d \
./libDrivers/src/mag.d \
./libDrivers/src/microsd.d \
./libDrivers/src/rtc.d \
./libDrivers/src/sleep.d \
./libDrivers/src/spi.d \
./libDrivers/src/tempsense.d 


# Each subdirectory must supply rules for building sources it contributes
libDrivers/src/codeflash.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/codeflash.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/codeflash.d" -MT"libDrivers/src/codeflash.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/dmactrl.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/dmactrl.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/dmactrl.d" -MT"libDrivers/src/dmactrl.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/fatfs.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/fatfs.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/fatfs.d" -MT"libDrivers/src/fatfs.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/fram.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/fram.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/fram.d" -MT"libDrivers/src/fram.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/gyro.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/gyro.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/gyro.d" -MT"libDrivers/src/gyro.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/i2c.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/i2c.d" -MT"libDrivers/src/i2c.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/low_power_tick_management.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/low_power_tick_management.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/low_power_tick_management.d" -MT"libDrivers/src/low_power_tick_management.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/mag.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/mag.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/mag.d" -MT"libDrivers/src/mag.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/microsd.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/microsd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/microsd.d" -MT"libDrivers/src/microsd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/rtc.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/rtc.d" -MT"libDrivers/src/rtc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/sleep.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/sleep.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/sleep.d" -MT"libDrivers/src/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/spi.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/spi.d" -MT"libDrivers/src/spi.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libDrivers/src/tempsense.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/libDrivers/src/tempsense.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libDrivers/src/tempsense.d" -MT"libDrivers/src/tempsense.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


