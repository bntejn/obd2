/** LCD (NHD-0420H1Z-FL-GBW-33V3) setup and write function.
 * Brought from its datasheet.
 * spec: 4 lines x 20 characters
 */

#include "common.h"
#include "lcd.h"
#include <string.h>

void print_portb(char *msg) {
    print_char(' ');
    char buffer[80];
    char tmp[10];
    for (int i=0; i<8; i++) {
        tmp[i] = PORTB & (0x80 >> i) ? '1' : '0';
    }
    tmp[8] = '\0';
    sprintf(buffer, "\"%s\" %s(0x%x) | ", msg, tmp, PORTB);
    print_str(buffer);
}


//4-bit Initialization:

void lcd_cmd(char i) {
    //char lower = i << 4;
    LCDOUT = i;         //put data on output Port
    //LCDOUT = lower;         //put data on output Port
    CLR(PORTD, PORTD1); //D/I=LOW : send instruction
    CLR(PORTD, PORTD0); //R/W=LOW : Write
    nybble();           //Send lower 4 bits
    i = i << 4;         //Shift over by 4 bits
    LCDOUT = i;
    nybble();           //Send upper 4 bits
}

void lcd_write(char i) {
    //char lower = i << 4;
    LCDOUT = i;         //put data on output Port
    SET(PORTD, PORTD1); // D/I=HIGH: send data
    CLR(PORTD, PORTD0); // R/W=LOW: write
    nybble();           //Clock lower 4 bits
    i = i << 4;         //Shift over by 4 bits
    LCDOUT = i;         //put data on output Port
    nybble();           //Clock upper 4 bits
}

void nybble() {
    SET(PORTD, PORTD4);
    _delay_ms(300);       //enable pulse width >= 300ns
    //print_char('n');
    CLR(PORTD, PORTD4); //Clock enable: falling edge
}

void lcd_init() {
    SET(DDRD, DDD6);
    SET(PORTD, PORTD6);
    PULLUP_OUT_REGS();
    LCDOUT = 0;
    _delay_ms(1000);
    _delay_ms(1000);
    _delay_ms(10); //Wait >40 msec after power is applied
    LCDOUT = 0x30; //put 0x30 on the output port
    _delay_ms(5); //must wait 5ms, busy flag not available
    nybble(); //command 0x30 = Wake up
    _delay_ms(10); //must wait 160us, busy flag not available
    nybble(); //command 0x30 = Wake up #2
    _delay_ms(10); //must wait 160us, busy flag not available
    nybble(); //command 0x30 = Wake up #3
    _delay_ms(10); //must wait 160us, busy flag not available
    nybble(); //command 0x30 = Wake up #3
    _delay_ms(10); //can check busy flag now instead of delay
    LCDOUT = 0x20; //put 0x20 on the output port
    nybble(); //Function set: 4-bit interface
    print_portb("after 0x20");
    lcd_cmd(0x28); //Function set: 4-bit/2-line
    lcd_cmd(0x10); //Set cursor
    lcd_cmd(0x0F); //Display ON; Blinking cursor
    lcd_cmd(0x06); //Entry Mode set
    print_portb("after 0x06");
}

