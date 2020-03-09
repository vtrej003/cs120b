/*      Author: Vincent Trejo
 *      Description: CS120B Final Project - ADC.h
 *      I acknowledge all content contained herein is my own original work. */

#ifndef __ADC_h__
#define __ADC_h__
#include <avr/io.h>

void ADC_init();// Call this in main.c to Change PORTA to ADC Registers.

void ADC_SetPin(unsigned char);//Input the pin number thats connected to the component.

/*The special register that contains the value is ADC. char input = ADC& 0xFF*/
uint16_t ADC_Read();

#endif
