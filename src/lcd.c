/** LCD (NHD-0420H1Z-FL-GBW-33V3) setup and write function.
 * Brought from its datasheet.
 * spec: 4 lines x 20 characters
 */

#include "common.h"
#include "lcd.h"

//4-bit Initialization:

void lcd_cmd(char i) {
//    i = i<<4;
    PORTB |= (i << 4); //put data on output Port
    //CD_I =0; //D/I=LOW : send instruction
    //R_W =0; //R/W=LOW : Write
    CLR(PORTD, PORTD2);
    CLR(PORTD, PORTD3);
    nybble(); //Send lower 4 bits
    //i = i<<4; //Shift over by 4 bits
    //P1 = i; //put data on output Port
    PORTB |= i << 8;
    nybble(); //Send upper 4 bits
}

void lcd_write(char i) {
    //P1 = i; //put data on output Port
    PORTB |= i << 4;
    //D_I =1; //D/I=HIGH : send data
    //R_W =0; //R/W=LOW : Write
    SET(PORTD, PORTD2);
    CLR(PORTD, PORTD3);
    nybble(); //Clock lower 4 bits
    //i = i<<4; //Shift over by 4 bits
    //P1 = i; //put data on output Port
    PORTB |= i << 8;
    nybble(); //Clock upper 4 bits
}

void nybble() {
    //E = 1;
    SET(PORTD, PORTD1);
    _delay_ms(1); //enable pulse width >= 300ns
    //E = 0; //Clock enable: falling edge
    CLR(PORTD, PORTD1);
}

void lcd_init() {
    // pull up
    SET(DDRB, DDB1);
    SET(DDRB, DDB2);
    SET(DDRB, DDB3);
    SET(DDRB, DDB4);
    SET(DDRB, DDB5);
    SET(DDRB, DDB6);
    SET(DDRB, DDB7);

    P1 = 0;
    //P3 = 0;
    _delay_ms(100); //Wait >40 msec after power is applied
    P1 = 0x30; //put 0x30 on the output port
    _delay_ms(30); //must wait 5ms, busy flag not available
    nybble(); //command 0x30 = Wake up
    _delay_ms(10); //must wait 160us, busy flag not available
    nybble(); //command 0x30 = Wake up #2
    _delay_ms(10); //must wait 160us, busy flag not available
    nybble(); //command 0x30 = Wake up #3
    _delay_ms(10); //can check busy flag now instead of delay
    P1= 0x20; //put 0x20 on the output port
    nybble(); //Function set: 4-bit interface
    lcd_cmd(0x28); //Function set: 4-bit/2-line
    lcd_cmd(0x10); //Set cursor
    lcd_cmd(0x0F); //Display ON; Blinking cursor
    lcd_cmd(0x06); //Entry Mode set
}

