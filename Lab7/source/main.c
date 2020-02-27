/*
 * borte012_lab6_part2.c
 * Author : Briana
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

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

/*enum syncSM { start, init, led1, led2, led3, wait1, wait2, wait3, stop1, stop2, stop3, waitB1, waitB2, waitB3} state;*/
enum syncSM { start, init, led, pause, resume} state;
void syncSM_tick();

unsigned char button;
unsigned char ledIndex;

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(100);
    TimerOn();
    state = start;
    //unsigned char tmpB = 0x00;
    while (1)
    {
            syncSM_tick();
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
}

void syncSM_tick()
{
	button = (~PINA & 0x01);

        switch(state)//transition
	{
		case start:
			
			break;
		case init:
			
			break;
		case led:
			if (button == 0x00)
			{
			    break;
			}
			else if ( button == 0x01)
			{
			    state = pause;
			    break;
			}
			else
			{
			    break;
			}
			
			break;
			
		case pause:
			if(button == 0)
			{
			    state = resume;
			    break;
			}
			else if(button == 1)
			{
			    state = pause;
			    break;
			}
			else
			{
			    break;
			}
		case resume:
			if(button == 0x01)
			{
			    state = led;
			    break;
			}
			else 
			{
			    state = resume;
			    break;
			}
		
		default : 
			break;	
	}
	
	 switch(state)//actions
	 {

		 case start:
			 state = init;
			break;
		 case init:
			PORTA = 0x00;
			PORTB = 0x00;
			button = 0x00;
			ledIndex = 0x01;
			state = led;
		        break;
		 case led:
			if(ledIndex > 0x03)
			{
			    ledIndex = 0x01;
			    break;
			}
			else
			{
			    ledIndex = (ledIndex << 1);
			    break;
			}
		 case pause:
			// set time flag to 0 until button pressed
                        
			if(button == 0x01)
			{
			    TimerOff();
			    TimerFlag = 1;
			    break;
			}
			else if(button == 0x00)
			{
				break;
			}
			else
			{
			    break;
	                }
		case resume:
			TimerOn();
			break;

		 default :
			break;
	 }
	 PORTB = ledIndex;
}
