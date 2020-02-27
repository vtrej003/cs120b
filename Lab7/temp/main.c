/*	Author: root
 *  Partner(s) Name: Briana
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Initializes the LCD display*/
    LCD_init();

    /* Starting at position 1 on the LCD screen, writes Hello World*/
    LCD_DisplayString(1, "Hello World");

    while (1) {
        continue;
    }
    
}
