################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include libcsp/src/transport/subdir.mk
-include libcsp/src/rtable/subdir.mk
-include libcsp/src/interfaces/subdir.mk
-include libcsp/src/drivers/usart/subdir.mk
-include libcsp/src/drivers/i2c/subdir.mk
-include libcsp/src/drivers/can/subdir.mk
-include libcsp/src/crypto/subdir.mk
-include libcsp/src/arch/windows/subdir.mk
-include libcsp/src/arch/posix/subdir.mk
-include libcsp/src/arch/macosx/subdir.mk
-include libcsp/src/arch/freertos/subdir.mk
-include libcsp/src/subdir.mk
-include libcsp/examples/subdir.mk
-include libcsp/build/src/arch/posix/subdir.mk
-include libcsp/build/conf_check_eab097b9a75bdde1ddeac7e68b5cb77d/testbuild/subdir.mk
-include libcsp/build/conf_check_eab097b9a75bdde1ddeac7e68b5cb77d/subdir.mk
-include libcsp/build/conf_check_e529220e978b1160ae643bdac5bcce76/testbuild/subdir.mk
-include libcsp/build/conf_check_e529220e978b1160ae643bdac5bcce76/subdir.mk
-include libcsp/build/conf_check_c034ce048e115614dc20ba0d73d1f67a/testbuild/subdir.mk
-include libcsp/build/conf_check_c034ce048e115614dc20ba0d73d1f67a/subdir.mk
-include libcsp/build/conf_check_ab9b2a6bd270a92e66d3a56f80d52b88/testbuild/subdir.mk
-include libcsp/build/conf_check_ab9b2a6bd270a92e66d3a56f80d52b88/subdir.mk
-include libcsp/build/conf_check_93e270be96cf9fba4c08adfe907d3f55/testbuild/subdir.mk
-include libcsp/build/conf_check_93e270be96cf9fba4c08adfe907d3f55/subdir.mk
-include libcsp/build/conf_check_74b97f683a5b3ecc1e1712cfdfbd54c5/testbuild/subdir.mk
-include libcsp/build/conf_check_74b97f683a5b3ecc1e1712cfdfbd54c5/subdir.mk
-include libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/testbuild/subdir.mk
-include libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/subdir.mk
-include libcsp/build/conf_check_3b632b1309534a29f18d28d23263e0b8/testbuild/subdir.mk
-include libcsp/build/conf_check_3b632b1309534a29f18d28d23263e0b8/subdir.mk
-include libcsp/build/conf_check_1de62bcbaf5dd85dc9ae9b63f153dc4a/testbuild/subdir.mk
-include libcsp/build/conf_check_1de62bcbaf5dd85dc9ae9b63f153dc4a/subdir.mk
-include libcsp/build/conf_check_1b24b0b3c24d53ce072660942760a09c/testbuild/subdir.mk
-include libcsp/build/conf_check_1b24b0b3c24d53ce072660942760a09c/subdir.mk
-include libDrivers/src/subdir.mk
-include emlib/subdir.mk
-include FreeRTOS/Source/portable/MemMang/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS/Source/subdir.mk
-include FatFS/src/subdir.mk
-include CMSIS/efm32gg/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main.axf

# Tool invocations
main.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "main.ld" -Xlinker --gc-sections -Xlinker -Map="main.map" --specs=nano.specs -o main.axf "./src/InitDevice.o" "./main.o" "./libcsp/src/transport/csp_rdp.o" "./libcsp/src/transport/csp_udp.o" "./libcsp/src/rtable/csp_rtable_cidr.o" "./libcsp/src/rtable/csp_rtable_static.o" "./libcsp/src/interfaces/csp_if_can.o" "./libcsp/src/interfaces/csp_if_i2c.o" "./libcsp/src/interfaces/csp_if_kiss.o" "./libcsp/src/interfaces/csp_if_lo.o" "./libcsp/src/interfaces/csp_if_zmqhub.o" "./libcsp/src/drivers/usart/usart_linux.o" "./libcsp/src/drivers/usart/usart_windows.o" "./libcsp/src/drivers/i2c/i2c_efm32.o" "./libcsp/src/drivers/can/can_at90can128.o" "./libcsp/src/drivers/can/can_at91sam7a1.o" "./libcsp/src/drivers/can/can_at91sam7a3.o" "./libcsp/src/drivers/can/can_socketcan.o" "./libcsp/src/csp_bridge.o" "./libcsp/src/csp_buffer.o" "./libcsp/src/csp_conn.o" "./libcsp/src/csp_crc32.o" "./libcsp/src/csp_debug.o" "./libcsp/src/csp_dedup.o" "./libcsp/src/csp_endian.o" "./libcsp/src/csp_iflist.o" "./libcsp/src/csp_io.o" "./libcsp/src/csp_port.o" "./libcsp/src/csp_promisc.o" "./libcsp/src/csp_qfifo.o" "./libcsp/src/csp_route.o" "./libcsp/src/csp_service_handler.o" "./libcsp/src/csp_services.o" "./libcsp/src/csp_sfp.o" "./libcsp/src/crypto/csp_hmac.o" "./libcsp/src/crypto/csp_sha1.o" "./libcsp/src/crypto/csp_xtea.o" "./libcsp/src/arch/windows/csp_malloc.o" "./libcsp/src/arch/windows/csp_queue.o" "./libcsp/src/arch/windows/csp_semaphore.o" "./libcsp/src/arch/windows/csp_system.o" "./libcsp/src/arch/windows/csp_thread.o" "./libcsp/src/arch/windows/csp_time.o" "./libcsp/src/arch/windows/windows_queue.o" "./libcsp/src/arch/posix/csp_malloc.o" "./libcsp/src/arch/posix/csp_queue.o" "./libcsp/src/arch/posix/csp_semaphore.o" "./libcsp/src/arch/posix/csp_system.o" "./libcsp/src/arch/posix/csp_thread.o" "./libcsp/src/arch/posix/csp_time.o" "./libcsp/src/arch/posix/pthread_queue.o" "./libcsp/src/arch/macosx/csp_malloc.o" "./libcsp/src/arch/macosx/csp_queue.o" "./libcsp/src/arch/macosx/csp_semaphore.o" "./libcsp/src/arch/macosx/csp_system.o" "./libcsp/src/arch/macosx/csp_thread.o" "./libcsp/src/arch/macosx/csp_time.o" "./libcsp/src/arch/macosx/pthread_queue.o" "./libcsp/src/arch/freertos/csp_malloc.o" "./libcsp/src/arch/freertos/csp_queue.o" "./libcsp/src/arch/freertos/csp_semaphore.o" "./libcsp/src/arch/freertos/csp_system.o" "./libcsp/src/arch/freertos/csp_thread.o" "./libcsp/src/arch/freertos/csp_time.o" "./libcsp/examples/csp_if_fifo.o" "./libcsp/examples/csp_if_fifo_windows.o" "./libcsp/examples/kiss.o" "./libcsp/examples/simple.o" "./libcsp/build/conf_check_eab097b9a75bdde1ddeac7e68b5cb77d/test.o" "./libcsp/build/conf_check_e529220e978b1160ae643bdac5bcce76/test.o" "./libcsp/build/conf_check_c034ce048e115614dc20ba0d73d1f67a/test.o" "./libcsp/build/conf_check_ab9b2a6bd270a92e66d3a56f80d52b88/test.o" "./libcsp/build/conf_check_93e270be96cf9fba4c08adfe907d3f55/test.o" "./libcsp/build/conf_check_74b97f683a5b3ecc1e1712cfdfbd54c5/test.o" "./libcsp/build/conf_check_665018f86b0ec8bf077655ad79aebac7/test.o" "./libcsp/build/conf_check_3b632b1309534a29f18d28d23263e0b8/test.o" "./libcsp/build/conf_check_1de62bcbaf5dd85dc9ae9b63f153dc4a/test.o" "./libcsp/build/conf_check_1b24b0b3c24d53ce072660942760a09c/test.o" "./libDrivers/src/codeflash.o" "./libDrivers/src/dmactrl.o" "./libDrivers/src/fatfs.o" "./libDrivers/src/fram.o" "./libDrivers/src/gyro.o" "./libDrivers/src/i2c.o" "./libDrivers/src/low_power_tick_management.o" "./libDrivers/src/mag.o" "./libDrivers/src/microsd.o" "./libDrivers/src/rtc.o" "./libDrivers/src/sleep.o" "./libDrivers/src/spi.o" "./libDrivers/src/tempsense.o" "./emlib/em_acmp.o" "./emlib/em_adc.o" "./emlib/em_aes.o" "./emlib/em_assert.o" "./emlib/em_burtc.o" "./emlib/em_cmu.o" "./emlib/em_cryotimer.o" "./emlib/em_crypto.o" "./emlib/em_dac.o" "./emlib/em_dbg.o" "./emlib/em_dma.o" "./emlib/em_ebi.o" "./emlib/em_emu.o" "./emlib/em_gpcrc.o" "./emlib/em_gpio.o" "./emlib/em_idac.o" "./emlib/em_int.o" "./emlib/em_lcd.o" "./emlib/em_ldma.o" "./emlib/em_lesense.o" "./emlib/em_letimer.o" "./emlib/em_leuart.o" "./emlib/em_mpu.o" "./emlib/em_msc.o" "./emlib/em_opamp.o" "./emlib/em_pcnt.o" "./emlib/em_prs.o" "./emlib/em_rmu.o" "./emlib/em_rtc.o" "./emlib/em_rtcc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_vcmp.o" "./emlib/em_wdog.o" "./FreeRTOS/Source/croutine.o" "./FreeRTOS/Source/event_groups.o" "./FreeRTOS/Source/list.o" "./FreeRTOS/Source/queue.o" "./FreeRTOS/Source/tasks.o" "./FreeRTOS/Source/timers.o" "./FreeRTOS/Source/portable/MemMang/heap_4.o" "./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o" "./FatFS/src/diskio.o" "./FatFS/src/ff.o" "./CMSIS/efm32gg/startup_gcc_efm32gg.o" "./CMSIS/efm32gg/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: main.hex'
	arm-none-eabi-objcopy -O ihex "main.axf" "main.hex"
	@echo ' '

	@echo 'Building bin file: main.bin'
	arm-none-eabi-objcopy -O binary "main.axf" "main.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "main.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) main.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
