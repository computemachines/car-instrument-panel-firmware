#include "lcm_character_display.h"

#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/time.h"

#include "lcm_send.pio.h"
#include "common.h"

PIO GLOBAL_LCM_PIO = pio0;
uint GLOBAL_LCM_SM = -1;

uint8_t reverse_bits(uint8_t b)
{
    // println_bin_8(b);
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    // println_bin_8(b);
    // printf("\n");
    return b;
}

/* Initialize LCM display in 8 bit mode */
void lcm_init()
{
    //uint32_t lcm_control_mask = (1 << LCM_RS) | (1 << LCM_RW) | (1 << LCM_E);
    //uint32_t lcm_mask = lcm_control_mask | LCM_DB_MASK;
    //gpio_init_mask(lcm_mask);
    //gpio_set_dir_out_masked(lcm_mask);

    //GLOBAL_LCM_PIO = pio0;
    uint offset = pio_add_program(GLOBAL_LCM_PIO, &lcm_send_program);
    GLOBAL_LCM_SM = pio_claim_unused_sm(GLOBAL_LCM_PIO, true);
    lcm_send_program_init(GLOBAL_LCM_PIO, GLOBAL_LCM_SM, offset, LCM_DB7, LCM_E, LCM_RS);

    sleep_ms(100);
    lcm_instr(reverse_bits(0b00110000));
    sleep_ms(5);
    lcm_instr(reverse_bits(0b00110000));
    sleep_us(150);
    lcm_instr(reverse_bits(0b00110000));

    lcm_instr(reverse_bits(0b00111000));
    lcm_instr(reverse_bits(0b00001100));
    lcm_instr(reverse_bits(0b00000001));
    lcm_instr(reverse_bits(0b00000110));
// #define NUM_COMMANDS 8
//     command_t commands[NUM_COMMANDS] = {
//         {REV_BIT8(5) | REV_BIT8(4), LCM_INSTR_MODE, LCM_DELAY_SHORT}, // initialization codes
//         {REV_BIT8(5) | REV_BIT8(4), LCM_INSTR_MODE, LCM_DELAY_SHORT},
//         {REV_BIT8(5) | REV_BIT8(4), LCM_INSTR_MODE, LCM_DELAY_SHORT},
//         {reverse_bits(0b00111000), LCM_INSTR_MODE, LCM_DELAY_SHORT},
//         {reverse_bits(0b00001100), LCM_INSTR_MODE, LCM_DELAY_SHORT},
//         {reverse_bits(0b00000001), LCM_INSTR_MODE, LCM_DELAY_SHORT},
//         {reverse_bits(0b00000110), LCM_INSTR_MODE, LCM_DELAY_SHORT},
//         {0b11111111},
//     };
// 
//     for (int i = 0; i < NUM_COMMANDS; i++)
//     {
//         pio_sm_put_blocking(pio, sm, commands[i].command_word);
//         println_bin_32(commands[i].command_word);
//         printf("%d ", i);
//     }
}

void lcm_instr(uint8_t instruction)
{
    bool delay_flag = LCM_DELAY_SHORT;
    switch (instruction) {
        case 0b1000000:
        case 0b0100000:
        case 0b1100000:
            delay_flag = LCM_DELAY_LONG;
            break;
        default:
            delay_flag = LCM_DELAY_SHORT;
    }

    command_t command = {instruction, LCM_INSTR_MODE, delay_flag};
    pio_sm_put_blocking(GLOBAL_LCM_PIO, GLOBAL_LCM_SM, command.command_word);
}

void lcm_set_location(uint8_t row, uint8_t column) {
    uint8_t addr = (0x40)*row + column;
    lcm_instr(LCM_SETDDRAMADDR | reverse_bits(addr));
}


void lcm_data(uint8_t data)
{
    command_t command = {data, LCM_DATA_MODE, LCM_DELAY_SHORT};
    pio_sm_put_blocking(GLOBAL_LCM_PIO, GLOBAL_LCM_SM, command.command_word);
}
void lcm_data_reversed(uint8_t data)
{
    lcm_data(reverse_bits(data));
}
void lcm_write_string(char *string)
{
    for(char *character = string; *character != '\0'; character ++) {
        lcm_data_reversed(*character);
    }
}

//
///* Write bits to LCM bus. Bits are in reversed order. LSb <=> LCM_DB7 */
//void lcm_write(uint8_t value, uint8_t data_instr_mode)
//{
//    gpio_put(LCM_RS, data_instr_mode);
//    gpio_put(LCM_RW, false);
//    // println_bin_32(LCM_DB_MASK);
//    // println_bin_32(LCM_SHIFT_INTO_DB(value));
//    gpio_put_masked(LCM_DB_MASK, LCM_SHIFT_INTO_DB(value));
//    lcm_pulse_enable();
//}
//
//void lcm_pulse_enable()
//{
//    // gpio_put(LCM_E, false);
//    sleep_us(50);
//    gpio_put(LCM_E, true);
//    sleep_us(80);
//    gpio_put(LCM_E, false);
//    sleep_us(50);
//}
