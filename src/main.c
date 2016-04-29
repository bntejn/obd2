#include "common.h"
#include "lcd.h"
#include "serial.h"
#include <stdio.h>

int main() {
    SETUP_LEDS();
    setup_serial();
    lcd_init();
    
    lcd_write(' ');
    lcd_write('h');
    lcd_write('e');
    lcd_write('l');
    lcd_write('l');
    lcd_write('o');
    //lcd_write('b');
    //lcd_write('c');
    while (true) {
        SET(PORTC, PORTC7);
        _delay_ms(10);
        CLR(PORTC, PORTC7);
        _delay_ms(2);
    }

    return 0;
}

