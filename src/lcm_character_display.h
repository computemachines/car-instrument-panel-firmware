#ifndef __PROJECTS_CAR_INSTRUMENT_PANEL_FIRMWARE_SRC_LCM_CHARACTER_DISPLAY_H_
#define __PROJECTS_CAR_INSTRUMENT_PANEL_FIRMWARE_SRC_LCM_CHARACTER_DISPLAY_H_

#include "pico/stdlib.h"
#include "hardware/pio.h"

#define LCM_8BIT

#define LCM_RS 13
#define LCM_RW 12
#define LCM_E 11

#ifdef LCM_8BIT
#define LCM_DB0 10
#define LCM_DB1 9
#define LCM_DB2 8
#define LCM_DB3 7
#endif /* LCM_8BIT */

#define LCM_DB4 6
#define LCM_DB5 5
#define LCM_DB6 4
#define LCM_DB7 3

#ifdef LCM_8BIT
#define LCM_DB_MASK 0x07F8
#define LCM_DB_START LCM_DB7
#else
#define LCM_DB_MASK 0x0078
#define LCM_DB_START LCM_DB3
#endif

#define LCM_SHIFT_INTO_DB(value) (value << LCM_DB_START)

#define LCM_INSTR_MODE 0
#define LCM_DATA_MODE 1
#define LCM_DELAY_SHORT 0
#define LCM_DELAY_LONG 1

#define BIT(bit) (1 << bit)
// #define REV_BIT8(bit) BIT(bit)
#define REV_BIT8(bit) (1 << (7-bit))


// // commands
#define LCM_CLEARDISPLAY REV_BIT8(0)
#define LCM_RETURNHOME REV_BIT8(1)
#define LCM_ENTRYMODESET REV_BIT8(2)
#define LCM_DISPLAYCONTROL REV_BIT8(3)
#define LCM_CURSORSHIFT REV_BIT8(4)
#define LCM_FUNCTIONSET REV_BIT8(5)
#define LCM_SETCGRAMADDR REV_BIT8(6)
#define LCM_SETDDRAMADDR REV_BIT8(7)

// // flags for display entry mode
#define LCM_ENTRYRIGHT 0x00
#define LCM_ENTRYLEFT REV_BIT8(1)
#define LCM_ENTRYSHIFTINCREMENT REV_BIT8(0)
#define LCM_ENTRYSHIFTDECREMENT 0x00

// // flags for display on/off control
#define LCM_DISPLAYON REV_BIT8(2)
#define LCM_DISPLAYOFF 0x00
#define LCM_CURSORON REV_BIT8(1)
#define LCM_CURSOROFF 0x00
#define LCM_BLINKON REV_BIT8(0)
#define LCM_BLINKOFF 0x00

// flags for display/cursor shift
#define LCM_DISPLAYMOVE REV_BIT8(3)
#define LCM_CURSORMOVE 0x00
#define LCM_MOVERIGHT REV_BIT8(2)
#define LCM_MOVELEFT 0x00


// // flags for function set
#define LCM_8BITMODE REV_BIT8(3)
#define LCM_4BITMODE 0x00
#define LCM_2LINE REV_BIT8(4)
#define LCM_1LINE 0x00
#define LCM_5x10DOTS REV_BIT8(5)
#define LCM_5x8DOTS 0x00


typedef union {
    struct {
        uint32_t data          : 8;
        uint32_t mode          : 1;
        uint32_t sleep_us_time : 1;
        uint32_t _RESERVED     : 22;
    };
    uint32_t command_word;
} command_t;

extern PIO GLOBAL_LCM_PIO;
extern uint GLOBAL_LCM_SM;

uint8_t reverse_bits(uint8_t b);
void lcm_init();
void lcm_write(uint8_t value, uint8_t mode);
void lcm_instr(uint8_t);
void lcm_data(uint8_t);
void lcm_data_reversed(uint8_t);
void lcm_set_location(uint8_t row, uint8_t column);
void lcm_write_string(char *string);
void lcm_command(command_t *command);
void lcm_pulse_enable();

#endif // __PROJECTS_CAR_INSTRUMENT_PANEL_FIRMWARE_SRC_LCM_CHARACTER_DISPLAY_H_
