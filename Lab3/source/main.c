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
    
    DDRC = 0xFF; PORTC = 0x00;
    
   
    //unsigned char tmpP = 0x00;
    //unsigned char tmpC =0x00;
    //unsigned char tmpA = 0x00;
    while(1){
        unsigned char tmpP = 0x00;
        unsigned char tmpC =0x00;
        unsigned char tmpA = 0x00;
 
   
	
	tmpA = PINA;
	//tmpA = tmpA & 0x0F;
        
        if( (0 < tmpA) && (tmpA < 3))
            tmpC = 0x20;
	else if((2 < tmpA) && (tmpA < 5))
            tmpC = 0x30;
        else if((4 < tmpA) && (tmpA < 7))
            tmpC = 0x38;
        else if(( 6 < tmpA) && (tmpA < 10))
            tmpC = 0x3C;
        else if(( 9 < tmpA) && (tmpA < 13))
            tmpC = 0x3E;
        else if( (12 < tmpA) && (tmpA < 16))
            tmpC = 0x3F;
	else{}

        if(tmpC < 4)
	{
	    tmpC = (tmpC | 0x40);
	}
        
	//tmpP = (PINA >> 4);


	if(((tmpP & 0x01) ==  1) && ((tmpP & 0x02) == 2) && ((tmpP & 0x04) == 0))
	{ 
 	    tmpC = (tmpC | 0x80);
	}
        else
	{
	    
	}
        PORTC = tmpC;	
    }
    return 0;
}
