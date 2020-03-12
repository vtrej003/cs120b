/*	Author: Vincent Trejo
 *  Partner(s) Name: 
 *	Lab Section:21
 *	Assignment: Lab #2  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    DDRD = 0xFF; PORTD = 0x00;
    unsigned char tmpA = 0x00;
    
    
    while(1) 
    {
        PORTC = 0x04;
	PORTD = 0x00;
        tmpA = PINA;
        
	for(int i = 0 ; i < 4; i++)//lowest nib
	{		    
   	    if (tmpA & 0x01)
	    {
                PORTC--;                           
            }
	    else{ }
	    tmpA = tmpA >> 1;
	}
	if(PORTC == 0)
	{
	    PORTC |= (0x01 << 7);
        }
    }
    return 1;    
}

