# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(SHIELD ssd1306_128x64)
set(DTC_OVERLAY_FILE nrf52840dk_nrf52840.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(OLED_Embedded_project)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE src/main.c src/bluetoothconnection.c src/ssd_display.c)

zephyr_library_include_directories(${ZEPHYR_BASE}/samples/bluetooth)
