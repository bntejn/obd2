#include "common.h"
#include "lcd.h"
#include "serial.h"
#include <stdio.h>

int main() {
    SETUP_LEDS();
    setup_serial();
    lcd_init();
    
    lcd_print_char('h');
    lcd_print_char('e');
    lcd_print_char('l');
    lcd_print_char('l');
    lcd_print_char('o');
    //lcd_print_char('b');
    //lcd_print_char('c');
    while (true) {
        SET(PORTC, PORTC7);
        _delay_ms(10);
        CLR(PORTC, PORTC7);
        _delay_ms(2);
    }

    return 0;
}

