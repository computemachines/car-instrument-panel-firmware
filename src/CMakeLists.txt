add_executable(car-instrument-panel)

pico_generate_pio_header(car-instrument-panel ${CMAKE_CURRENT_LIST_DIR}/lcm_send.pio)

target_sources(car-instrument-panel PRIVATE main.c led_segment_display.c lcm_character_display.c)
target_link_libraries(car-instrument-panel PRIVATE pico_stdlib hardware_gpio hardware_spi hardware_pio pico_time)
#target_compile_options(car-instrument-panel PRIVATE "-Werror")

pico_add_extra_outputs(car-instrument-panel)
pico_enable_stdio_usb(car-instrument-panel 1)
pico_enable_stdio_uart(car-instrument-panel 1)
