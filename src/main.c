#include "common.h"
#include "lcd.h"

int main() {
    lcd_init();
    
    SET(DDRD, DDD6);
    SET(PORTD, PORTD6);
    lcd_write('a');
    while (true) {
        _delay_ms(2000);
        turn_led_y(-1);
    }

    return 0;
}

