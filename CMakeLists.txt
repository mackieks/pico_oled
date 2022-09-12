cmake_minimum_required(VERSION 3.12)

set(PICO_BOARD "PIMORONI_TINY2040")

include(pico_sdk_import.cmake)

project(pico_oled C CXX ASM)

pico_sdk_init()

add_executable(pico_oled src/pico_oled.c src/ssd1351.c src/font.c)

pico_enable_stdio_usb(pico_oled 1)

pico_add_extra_outputs(pico_oled)

target_link_libraries( 
        pico_oled
        pico_stdlib
        pico_time
        hardware_dma
        hardware_spi
        )



