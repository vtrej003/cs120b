/*	Author: Vincent Trejo
 *	Description: CS120B Final Project - main.c
 *	I acknowledge all content contained herein is my own original work.
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../header/ADC.h"

unsigned short joyX;
unsigned short joyY;
//unsigned char joySW;

int main (void)
{
    DDRA = 0x00; PORTA = 0xFF;//input 
    DDRB = 0xFF; PORTB = 0x00;//out
    ADC_init();
    joyX = 0x00;
    joyY = 0x00;
      
    while(1)
    {
	
        ADC_SetPin(0);
	joyX = ADC & 0xFF;//record
	ADC_SetPin(1);// register will now record from the 2nd pin on A
	joyY = ADC & 0xFF;
        if((joyX != 0) || (joyY != 0))
	{
            PORTB = 0xFF;
	}
        _delay_ms(100);
    }    
}
