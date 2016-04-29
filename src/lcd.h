#ifndef LCD_H_
#define LCD_H_

#include "common.h"
#include "serial.h"


#define D_I PORTD1
#define R_W PORTD0
#define E   PORTD4 (4)
#define LCDOUT  PORTB

void lcd_init();

void lcd_cmd(char c);

void lcd_write(char c);

#define PULLUP_OUT_REGS() {\
    DDRB = 0xf0;\
    SET(DDRD, DDD1);\
    SET(DDRD, DDD0);\
    SET(DDRD, DDD4);\
    SET(DDRC, DDC7);\
}
// output-RS-RW-E

#endif

