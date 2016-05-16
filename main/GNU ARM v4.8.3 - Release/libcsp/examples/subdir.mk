################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/csp_if_fifo.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/csp_if_fifo_windows.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/kiss.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/simple.c 

OBJS += \
./libcsp/examples/csp_if_fifo.o \
./libcsp/examples/csp_if_fifo_windows.o \
./libcsp/examples/kiss.o \
./libcsp/examples/simple.o 

C_DEPS += \
./libcsp/examples/csp_if_fifo.d \
./libcsp/examples/csp_if_fifo_windows.d \
./libcsp/examples/kiss.d \
./libcsp/examples/simple.d 


# Each subdirectory must supply rules for building sources it contributes
libcsp/examples/csp_if_fifo.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/csp_if_fifo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/examples/csp_if_fifo.d" -MT"libcsp/examples/csp_if_fifo.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libcsp/examples/csp_if_fifo_windows.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/csp_if_fifo_windows.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/examples/csp_if_fifo_windows.d" -MT"libcsp/examples/csp_if_fifo_windows.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libcsp/examples/kiss.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/kiss.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/examples/kiss.d" -MT"libcsp/examples/kiss.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libcsp/examples/simple.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/examples/simple.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/examples/simple.d" -MT"libcsp/examples/simple.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


