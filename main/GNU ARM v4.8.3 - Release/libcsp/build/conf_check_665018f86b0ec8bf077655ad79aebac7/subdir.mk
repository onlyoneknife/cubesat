################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.c 

OBJS += \
./libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.o 

C_DEPS += \
./libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.d 


# Each subdirectory must supply rules for building sources it contributes
libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.o: C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/lib3rdParty/libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG280F1024=1' -I"C:/Users/sdamkjar/workspace/ualberta_athena_cubesatobc/main/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.d" -MT"libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


