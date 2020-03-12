/*      Author: Vincent Trejo
 *      Description: CS120B Final Project - main.c
 *      I acknowledge all content contained herein is my own original work.
 */
#define F_CPU 8000000
#define up 0x02
#define down 0x40
#define right 0x10
#define left 0x08

#define strLeft "left"
#define strRight "right"
#define strUp "up"
#define strDown "down"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../header/ADC.h"
#include "../header/usart.h"

uint16_t joyX;
uint16_t joyY;
volatile unsigned char count;
unsigned char LEDx, LEDy;
int main (void)
{
    DDRA = 0x00; PORTA = 0xFF;//input 
    DDRB = 0xFF; PORTB = 0x00;//out
    DDRD = 0xFF; PORTD = 0xFF;
    DDRC = 0xFF; PORTC = 0xFF;
    initUSART();
    ADC_init();
    joyX = 0;
    joyY = 0;
    LEDx = 0x00;
    LEDy = 0x00;
    count = 0x00;  
    while(1)
    {
	//USART_Flush();
        //USART_Send(count);
        ADC_SetPin(0);
        _delay_ms(100);
        joyX = ADC_Read();//record
            
        /*Horizontel LED*/
        if(joyX <= 400)
        {
            LEDx = left;
	   // USART_SendStr("left");
            USART_SendChar('l');

        }
        else if((joyX > 400) && (joyX < 600))
        {
            LEDx = 0x00;
        }
        else if(joyX >= 600)
        {
            LEDx =  right;
	   // USART_SendStr("right");
	    USART_SendChar('r');
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
            //USART_SendStr("up");
            USART_SendChar('l');

        }
        else if((joyY > 400) && (joyY < 600))
        {
            LEDy = 0x00;
        }
        else if(joyY >= 600)
        {
            LEDy =  down;
            //USART_SendStr("down");
            USART_SendChar('d');

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
        count++;
    }    
}

