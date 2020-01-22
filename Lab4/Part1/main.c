/* Author: Vincent Trejo 
 * Partner(s) Name: * Lab Section: 23
 * Assignment: Lab 4 Exercise 1
 * Exercise Description:
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */ 

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum StateMachine {start,init, wait, pressed, depress} currentState, nextState;

void ledSystem();

int main(void)
{
	
    DDRA = 0x00; PORTA = 0xFF; //initialize PORT A to 0xFF for input
    DDRB = 0xFF; PORTB = 0x00; //initialize PORT B to 0x00 for output	
    PORTB = 0x01;
    while (1)
    {

        ledSystem();
    }
    return 0;
}

void ledSystem()
{
    //transitions
    unsigned char flip = 0x00;
    
    switch(currentState)//transitions
    {
	case start :
	    nextState = init;
  	    break;
	case init :
	    nextState = wait;	
	    break;
	case wait :
	    if(PINA == 0x01)
	    {
	        nextState = pressed;
		
	    }
	    else 
	    {
	        nextState = currentState;
		
	    }
	    break;

	case pressed :
	    nextState = depress;
            break;

	case depress:
            if(PINA == 0x01)
	    {
                nextState = currentState;
	    }
	    else
	    {
                nextState = wait;
            }    
	    break;
	default:
	    nextState = currentState;
	    break;	
    }
	
	
    switch(currentState)//actions 
    {
	case start:
 	    break;
	case init:
	    PORTB = 0x01;
	    break;

	case wait:
	    break;

	case pressed:
	    if(PORTB == 0x01)
	    {
	        PORTB = 0x02;
	    }
	    else if(PORTB == 0x02)
	    {
	        PORTB = 0x01;
	    }
	    else
	    {
		break;
	    }
	    break;
	case depress:
	    break;
	default:
	    break;
    }
    currentState = nextState;

	
}

