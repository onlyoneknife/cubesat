#!/bin/bash

./waf configure \
	--with-driver-i2c="efm32" \
	--enable-if-i2c \
	--with-os=freertos \
	--with-drivers=../../libDrivers/inc \
	--enable-crc32 \
	