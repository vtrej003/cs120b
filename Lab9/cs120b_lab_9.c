/*
 borte012_lab10_part1.c
 Author : Briana
 Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
 Lab Section:021
 Assignment: Lab #10 Exercise #1
 Exercise Description:

 I acknowledge all content contained herein, excluding template or example
 code, is my own original work.
*/
/*===========LIBS=========================*/
#include <avr/io.h>
#include <avr/interrupt.h>


//Struct for Tasks represent a running process in our simple real-time operating system
typedef struct _task{
	// Tasks should have members that include: state, period,
	//a measurement of elapsed time, and a function pointer.
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;

/*=======SM===============================*/
enum CombineStates{ combine_read, combine_write} combineState;
enum ThreeLEDState{threeLed_off, threeLed_on} threeLedState;
enum BlinkingLEDState{blinkingLED_off, blinkingLed_on} blinkingLedState;

/*=========TIMER_Functions=======================*/
volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.
// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
void TimerOn();
void TimerOff();
void TimerISR();
ISR(TIMER1_COMPA_vect);
unsigned long int findGCD(unsigned long int a, unsigned long int b);
/*=========GLOBAL_FUNC====================*/
void blinkingLED_tick();
void threeLED_tick();
void CombineState_tick();

/*=========Global Var======================*/
unsigned char input;
unsigned char count;

/*=========MAIN============================*/
int main(void)
{
  DDRA = 0x00; PORTA = 0xFF;
  DDRB = 0xFF; PORTB = 0x00;
  
  while (1)
  {
      blinkingLED_tick();
      threeLED_tick();
      CombineState_tick();
	  while (!TimerFlag) {};
		  TimerFlag = 0;
  }
}

/*============SM_FUNC_DEFINE====================*/
void CombineState_tick()
{
  
  switch (combineState) //transition
  {
    case combine_read:
      break;
    case combine_write:
      break;
    default:
      combineState = combine_read;
      break;
  }

  switch (combineState) //actions
  {
    case combine_read:
      break;
    case combine_write:
      break;
    default :
      break;
  }
}
void threeLED_tick()
{
  switch (threeLedState) //transition
  {
    case threeLed_off:
      break;
    case threeLed_on:
      break;
    default:
      break;
  }

  switch (threeLedState) //action
  {
    case threeLed_off:
      break;
    case threeLed_on:
      break;
    default:
      break;
  }
}

void blinkingLED_tick()
{
  switch (blinkingLedState) //transition
  {
    case blinkingLED_off:
      break;
    case blinkingLed_on:
      break;
    default:
      break;
  }

   switch (blinkingLedState) //action
  {
     case blinkingLED_off:
      break;
    case blinkingLed_on:
      break;
    default:
      break;
  }
}
/*=========HELPER_FUNC_DEFINITIONS==============*/


/*====================TIMER===================*/
void TimerSet(unsigned long M) {
  _avr_timer_M = M;
  _avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
  // AVR timer/counter controller register TCCR1
  TCCR1B  = 0x0B; // bit3 = 1: CTC mode (clear timer on compare)
          // bit2bit1bit0=011: prescaler /64
          // 00001011: 0x0B
          // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
          // Thus, TCNT1 register will count at 125,000 ticks/s

  // AVR output compare register OCR1A.
  OCR1A   = 125;  // Timer interrupt will be generated when TCNT1==OCR1A
          // We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
          // So when TCNT1 register equals 125,
          // 1 ms has passed. Thus, we compare to 125.
          // AVR timer interrupt mask register

  TIMSK1  = 0x02; // bit1: OCIE1A -- enables compare match interrupt

  //Initialize avr counter
  TCNT1 = 0;

  // TimerISR will be called every _avr_timer_cntcurr milliseconds
  _avr_timer_cntcurr = _avr_timer_M;

  //Enable global interrupts
  SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
  TCCR1B  = 0x00; // bit3bit2bit1bit0=0000: timer off
}

void TimerISR() {
  TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
  // CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
  _avr_timer_cntcurr--;       // Count down to 0 rather than up to TOP
  if (_avr_timer_cntcurr == 0) {  // results in a more efficient compare
    TimerISR();         // Call the ISR that the user uses
    _avr_timer_cntcurr = _avr_timer_M;
  }
}

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
		if( c == 0 ) { return b; }
		a = b;
		b = c;
	}
	return 0;
}
