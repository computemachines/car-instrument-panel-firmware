add_executable(car-instrument-panel)
target_sources(car-instrument-panel PRIVATE main.c led_segment_display.c)
target_link_libraries(car-instrument-panel PRIVATE pico_stdlib hardware_gpio hardware_spi)

pico_add_extra_outputs(car-instrument-panel)
pico_enable_stdio_usb(car-instrument-panel 1)
pico_enable_stdio_uart(car-instrument-panel 0)