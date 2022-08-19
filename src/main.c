#include <stdio.h>
#include "pico/stdlib.h"

#include "led_segment_display.h"
#include "lcm_character_display.h"

int main()
{
    setup_default_uart();

    init_display();

    uint8_t digits[] = {1, 2, 3, 4};
    set_digits(digits, 3);

    display_loop();
    return 0;
}