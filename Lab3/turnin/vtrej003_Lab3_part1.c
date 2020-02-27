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
    unsigned char count = 0x00;
    unsigned char tmpP[2] = { 0x00 };
        
    while(1)
    {
	PORTC = 0x00;
	tmpP[0] = PINA;
        tmpP[1] = PINB;
        
        PORTD = ((PINB << 4) | PINA);//checking the input of both PINS
        for(int i = 0; i < 8; i++ )//Iterator through number of pins 8
        {
	    for(int j = 0; j < 2; j++)//iterates through the elements PINA and PINB
	    {
                if(tmpP[j] & (0x01)) // checks each element if there 1 pin is high and increments counter
	        {
                    PORTC++;
	        }
	        else
	        {

		}//does nothing

                //shift elements 
                tmpP[j] = (tmpP[j] >> 1);
            }
            
	    //tmpP[i] == (tmpP[i] << 1);
        }
    
    }
    return 0;
}
