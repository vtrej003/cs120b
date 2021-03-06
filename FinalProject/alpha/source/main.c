/*      Author: Vincent Trejo
 *      Description: CS120B Final Project - main.c
 *      I acknowledge all content contained herein is my own original work.
 */
#define F_CPU 8000000
#define up 0x02
#define down 0x40
#define right 0x10
#define left 0x08

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../header/ADC.h"
#include "../header/usart.h"

void sendChar(unsigned char);
uint16_t joyX;
uint16_t joyY;
//unsigned char count;
unsigned char LEDx, LEDy, flashLight;
int main (void)
{
    DDRA = 0x00; PORTA = 0xFF;//input 
    DDRB = 0x00; PORTB = 0xFF;//out
    DDRD = 0xFF; PORTD = 0x00;
    flashLight = 0;
    initUSART();
    ADC_init();
    joyX = 0;
    joyY = 0;
    LEDx = 0x00;
    LEDy = 0x00;
  //  count = 0;
    while(1)
    {
        ADC_SetPin(0);
        _delay_ms(100);
        joyX = ADC_Read();//record
        flashLight = (~PINB & 0x01);
	if(flashLight > 0)
	{
	    sendChar('f');
	    sendChar(flashLight);
	    
	    flashLight = !flashLight;
	    
	}
        /*Horizontel LED*/
        if(joyX <= 400)
        {
            LEDx = left;
	    sendChar('l');
            //USART_Send('l');
	    //USART_Send('\n');

        }
        else if((joyX > 400) && (joyX < 600))
        {
            LEDx = 0x00;
        }
        else if(joyX >= 600)
        {
            LEDx =  right;
	    sendChar('r');

        }
        else
        {
            LEDx = 0x00;
        }
        /*END HORIZONTAL*/
        

        
        ADC_SetPin(1);// register will now record from the 2nd pin on A
        _delay_ms(100);
        joyY = ADC_Read();
        //VERTICAL LED//
        if(joyY <= 400)
        {
            LEDy = up;
	    sendChar('u');

        }
        else if((joyY > 400) && (joyY < 600))
        {
            LEDy = 0x00;
        }
        else if(joyY >= 600)
        {
            LEDy =  down;
	    sendChar('d');

        }
        else
        {
            LEDy = 0x00;
        }
        //END VERTICAL//
        _delay_ms(100);

        PORTB = LEDx | LEDy;
        LEDx = 0x00;
        LEDy = 0x00;
       // count++;
//	if(count > 10)
//	    count = 0;
    }    
}

void sendChar(unsigned char c)
{
     USART_Send(c);
     USART_Send('\n');

}
