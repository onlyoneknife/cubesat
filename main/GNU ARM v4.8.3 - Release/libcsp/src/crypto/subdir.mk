################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/crypto/csp_hmac.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/crypto/csp_sha1.c \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/crypto/csp_xtea.c 

OBJS += \
./libcsp/src/crypto/csp_hmac.o \
./libcsp/src/crypto/csp_sha1.o \
./libcsp/src/crypto/csp_xtea.o 

C_DEPS += \
./libcsp/src/crypto/csp_hmac.d \
./libcsp/src/crypto/csp_sha1.d \
./libcsp/src/crypto/csp_xtea.d 


# Each subdirectory must supply rules for building sources it contributes
libcsp/src/crypto/csp_hmac.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/crypto/csp_hmac.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/src/crypto/csp_hmac.d" -MT"libcsp/src/crypto/csp_hmac.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libcsp/src/crypto/csp_sha1.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/crypto/csp_sha1.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/src/crypto/csp_sha1.d" -MT"libcsp/src/crypto/csp_sha1.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libcsp/src/crypto/csp_xtea.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/src/crypto/csp_xtea.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/src/crypto/csp_xtea.d" -MT"libcsp/src/crypto/csp_xtea.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


