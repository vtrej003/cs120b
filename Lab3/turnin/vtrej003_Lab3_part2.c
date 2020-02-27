/*      Author: root
 *  Partner(s) Name: henlo johnson
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    //unsigned count = 0x00;
    unsigned char tmpP = 0x00;
        
    while(1)
    {
	tmpP = PINA;
	PORTC = 0x00;
	PORTC = PINA;
	//tmpP = PINA;
        
        if( 0 < PORTC && PORTC< 3)
            PORTC = 0x20;
	else if( 2 < PORTC && PORTC < 5)
            PORTC = 0x30;
        else if( 4 < PORTC && PORTC < 7)
            PORTC = 0x38;
        else if( 6 < PORTC && PORTC < 10)
            PORTC = 0x3C;
        else if( 9 < PORTC && PORTC < 13)
            PORTC = 0x3E;
        else if( 12 < PORTC && PORTC < 16)
            PORTC = 0x3F;
	else{}

        if(PORTC < 4)
	{
	PORTC = (PORTC | 0x40);
	}
    }
    return 0;
}
