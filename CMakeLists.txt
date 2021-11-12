# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(OVERLAY_CONFIG "overlay-bt.conf")

#set(mcuboot_CONFIG_BOOT_SIGNATURE_KEY_FILE "\"${CMAKE_CURRENT_LIST_DIR}/signKeyRsa2048.pem\"")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(bootloaderTest)

target_sources(app PRIVATE src/main.c src/bluetooth.c)
#FILE(GLOB app_sources src/*.c)
#target_include_directories(app PRIVATE src)