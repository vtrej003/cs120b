
// Permission to copy is granted provided that this header remains intact. 
// This software is provided with no warranties.
#ifndef USART_H
#define USART_H
#include<avr/io.h>
// USART Setup Values
#define F_CPU 8000000 // Assume uC operates at 8MHz
#define BAUD_RATE 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)

void initUSART();
unsigned char USART_IsSendReady();
unsigned char USART_HasTransmitted();
unsigned char USART_HasReceived();
void USART_Flush();
void USART_Send(unsigned char sendMe);
unsigned char USART_Receive();
#endif //USART_H
