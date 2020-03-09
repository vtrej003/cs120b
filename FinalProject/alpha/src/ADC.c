/*      Author: Vincent Trejo
 *      Description: CS120B Final Project - main.c
 *      I acknowledge all content contained herein is my own original work.
 */
#include "../header/ADC.h"
#define divADC 6
void ADC_init()
{
    ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADATE);
    ADMUX |= (1 << ADLAR);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
}

void ADC_SetPin(unsigned char pin)
{
    if(pin < 8)
    {
        ADMUX &= 0xF8; // clear bottom 3 bits
        ADMUX |= pin; // then set bottom 3 bits to channel n
    }
}

uint16_t ADC_Read()
{
    return (ADC >> divADC);
}

