#ifndef __PROJECTS_CAR_INSTRUMENT_PANEL_FIRMWARE_SRC_LED_SEGMENT_DISPLAY_H_
#define __PROJECTS_CAR_INSTRUMENT_PANEL_FIRMWARE_SRC_LED_SEGMENT_DISPLAY_H_

#include "hardware/gpio.h"
#include "hardware/spi.h"

#define DIGIT_1 22
#define DIGIT_2 21
#define DIGIT_3 20
#define DIGIT_4 16
#define DIGITS_MASK ( \
        (1 << DIGIT_1) \
        | (1 << DIGIT_2) \
        | (1 << DIGIT_3) \
        | (1 << DIGIT_4)) 

#define SEGMENT_SPI spi0
#define SEGMENT_SPI_TX 19
#define SEGMENT_SPI_SCK 18
#define SEGMENT_SPI_CS 17

#define SEGMENT_A (1 << 1)
#define SEGMENT_B (1 << 3)
#define SEGMENT_C (1 << 5)
#define SEGMENT_D (1 << 7)
#define SEGMENT_E (1 << 0)
#define SEGMENT_F (1 << 2)
#define SEGMENT_G (1 << 4)
#define SEGMENT_DP (1 << 6)

uint8_t FRAMEBUFFER[4];

void led_init();

void led_disable();

void led_select_digit(uint8_t n);

void led_write_segments(uint8_t byte);
void led_write_digit(uint8_t byte, bool decimal);
void led_write_decimal_format(int16_t scaled_decimal, int8_t decade, uint8_t display_decimal_position, bool show_decimal_point);

uint8_t led_digit_to_segments(uint8_t digit);
void led_set_digits(uint8_t *digits, int8_t decimal_point_position);

void led_display_loop();

#endif // __PROJECTS_CAR_INSTRUMENT_PANEL_FIRMWARE_SRC_LED_SEGMENT_DISPLAY_H_
