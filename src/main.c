#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"

#include "led_segment_display.h"
#include "lcm_character_display.h"

#include "common.h"

int main()
{
    setup_default_uart();
    stdio_init_all();
    printf("\n\n\n\n----------\n");
    printf("waiting for usb host");
    while (!stdio_usb_connected()) {
      printf(".");
      sleep_ms(500);
    }
    printf("\nusb host detected!\n");
    led_init();

    uint8_t digits[] = {1, 2, 3, 4};
    led_set_digits(digits, 3);

    led_display_loop();
//
//    gpio_init(15);
//    gpio_init(LCM_RW);
//    gpio_set_dir(15, true);
//    gpio_set_dir(LCM_RW, true);
//    gpio_put(15, 1);
//    gpio_put(LCM_RW, 0);
//
//    sleep_ms(1000);
//
//    lcm_init();
//    lcm_set_location(0, 2);
//    lcm_write_string("Hello Worlds!");
//    printf("!");
//
//    while(true) {
//        tight_loop_contents();
//    }
//
    return 0;
}
