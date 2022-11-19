#include "led_segment_display.h"

#include "hardware/gpio.h"
#include "hardware/spi.h"

void led_init()
{
    gpio_init(DIGIT_1);
    gpio_set_dir(DIGIT_1, GPIO_OUT);
    gpio_init(DIGIT_2);
    gpio_set_dir(DIGIT_2, GPIO_OUT);
    gpio_init(DIGIT_3);
    gpio_set_dir(DIGIT_3, GPIO_OUT);
    gpio_init(DIGIT_4);
    gpio_set_dir(DIGIT_4, GPIO_OUT);

    spi_init(SEGMENT_SPI, 10000);
    gpio_set_function(SEGMENT_SPI_CS, GPIO_FUNC_SPI);
    gpio_set_function(SEGMENT_SPI_SCK, GPIO_FUNC_SPI);
    gpio_set_function(SEGMENT_SPI_TX, GPIO_FUNC_SPI);
}

void led_write_segments(const uint8_t byte)
{
    spi_write_blocking(spi0, &byte, 1);
}
void clear_segments()
{
    spi_write_blocking(SEGMENT_SPI, NULL, 1);
}
void led_write_digit(uint8_t digit, bool decimal_point)
{
    uint8_t optional_dp_segment = SEGMENT_DP * decimal_point;
    uint8_t digit_segments = led_digit_to_segments(digit);
    led_write_segments(digit_segments | optional_dp_segment);
}

void led_set_digits(uint8_t *digits, int8_t decimal_point_position)
{
    for (uint8_t i = 1; i <= 4; i++)
    {
        uint8_t dp;
        if (i == decimal_point_position) {
            dp = SEGMENT_DP;
        } else {
            dp = 0;
        }
        FRAMEBUFFER[i-1] = led_digit_to_segments(digits[i-1]) | dp;
    }
}

void led_display_loop()
{
    while (true)
    {
        for (int digit = 1; digit <= 4; digit++)
        {
            //clear_segments();
            //sleep_ms(1);
            //led_select_digit(digit);
            //led_write_segments(FRAMEBUFFER[digit-1]);
            uint8_t highs = 0xFF;
            spi_write_blocking(spi0, &highs, 1);
            sleep_ms(1);
        }
    }
}

void led_disable()
{
    gpio_put(DIGIT_1, false);
    gpio_put(DIGIT_2, false);
    gpio_put(DIGIT_3, false);
    gpio_put(DIGIT_4, false);
}

void led_select_digit(uint8_t n)
{
    led_disable();

    switch (n)
    {
    case 1:
        gpio_put(DIGIT_1, true);
        break;
    case 2:
        gpio_put(DIGIT_2, true);
        break;
    case 3:
        gpio_put(DIGIT_3, true);
        break;
    case 4:
        gpio_put(DIGIT_4, true);
        break;
    default:
        break;
    }
}

const uint8_t digits_lut[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,
    SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_E | SEGMENT_D,
    SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_C | SEGMENT_D,
    SEGMENT_F | SEGMENT_G | SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_C | SEGMENT_D,
    SEGMENT_A | SEGMENT_F | SEGMENT_E | SEGMENT_G | SEGMENT_D | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_F | SEGMENT_C,
};

uint8_t led_digit_to_segments(uint8_t digits)
{
    if (digits <= 9)
    {
        return digits_lut[digits];
    }
    else
    {
        return 0;
    }
}

void led_write_decimal_format(
    int16_t scaled_decimal,
    int8_t decade,
    uint8_t display_decimal_position,
    bool show_decimal_point)
{
}
