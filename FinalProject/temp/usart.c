#include "../header/usart.h"

void initUSART()
{
        UCSR0B|= (1 << RXEN0)  | (1 << TXEN0);
        UCSR0C|= (1 << UCSZ00) | (1 << UCSZ01);
        UBRR0L = BAUD_PRESCALE;
        UBRR0H = (BAUD_PRESCALE >> 8);
}
unsigned char USART_IsSendReady()
{
        return (UCSR0A & (1 << UDRE0));
}
unsigned char USART_HasTransmitted()
{
        return (UCSR0A & (1 << TXC0));
}
unsigned char USART_HasReceived()
{
        return (UCSR0A & (1 << RXC0));
}
void USART_Flush()
{
        static unsigned char dummy;
        while ( UCSR0A & (1 << RXC0) ) { dummy = UDR0; }
}
void USART_SendChar(unsigned char sendMe)
{
        while( !(UCSR0A & (1 << UDRE0)) );
        UDR0 = sendMe;
}
unsigned char USART_Receive()
{
        while ( !(UCSR0A & (1 << RXC0)) ); // Wait for data to be received
        return UDR0; // Get and return received data from buffer
}
void USART_SendStr(char *s)
{
   while (*s != 0x00)
   {
      USART_SendChar(*s);
      s++;
   }
} 

