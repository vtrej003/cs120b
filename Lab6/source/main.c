/*	Author: root
 *  Partner(s) Name: Briana
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*
 * borte012_lab6_part1.c
 * Author : Briana
 */ 

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff(){
	TCCR1B = 0x00;
}
void TimerISR(){
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum syncSM { start, init, led1, led2, led3, off} state;
void syncSM_tick();
void toggleState();

int main(void)
{
    DDRC = 0xFF;
    PORTC = 0x00;
    TimerSet(250);
    TimerOn();
	state = start;
    //unsigned char tmpB = 0x00;
    while (1)
    {
	    //tmpB = ~tmpB;
	    syncSM_tick();
	    while(!TimerFlag);
	    TimerFlag = 0;
            PORTC = 0x00;
    }
}

void toggleState()
{
	if((state == led1))
	{
		state = 3;
	}
	else if(state == 3 ){
		state = 4;
	}
	else if (state == 4){
		state = 2;
	}
	else
	{
	    state == 2;
	}	    
}
void syncSM_tick()
{
        switch(state)//transition
	{
		case start :
			state = init;
			break;
		case init :
			state = led1;
			break;
		case led1 :
			//state = off;
			break;
		case led2 :
			//state = off;
			break;
		case led3 :
			//state = off;
			break;
		case off :
			//toggleState();
			break;
		default : 
			break;	
	}
	
	 switch(state)//actions
	 {
		 case start :
			break;
		 case init :
			PORTC = 0x00;
		    break;
		 case led1 :
			PORTC = 0x01;
			toggleState();
			break;
		 case led2 :
			PORTC = 0x02;
			toggleState();
			break;
		 case led3 :
			PORTC = 0x04;
			toggleState();
			break;
		 case off :
			//PORTC = 0x00;
		    	
			break;
		 default :
			break;
	 }
}

