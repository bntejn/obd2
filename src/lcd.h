#ifndef LCD_H_
#define LCD_H_

#include "common.h"

#define P1  PORTB
#define P2  PORTB5
#define P3  PORTB6
#define P4  PORTB7
#define D_I PORTD2
#define R_W PORTD3
#define E   PORTD1

void lcd_init();

void lcd_cmd(char c);

void lcd_write(char c);


#endif

