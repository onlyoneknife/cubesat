################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/transport/csp_rdp.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/transport/csp_udp.c 

OBJS += \
./libcsp/src/transport/csp_rdp.o \
./libcsp/src/transport/csp_udp.o 

C_DEPS += \
./libcsp/src/transport/csp_rdp.d \
./libcsp/src/transport/csp_udp.d 


# Each subdirectory must supply rules for building sources it contributes
libcsp/src/transport/csp_rdp.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/transport/csp_rdp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/src/transport/csp_rdp.d" -MT"libcsp/src/transport/csp_rdp.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libcsp/src/transport/csp_udp.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/transport/csp_udp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/src/transport/csp_udp.d" -MT"libcsp/src/transport/csp_udp.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


