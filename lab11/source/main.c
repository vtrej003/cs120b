/*
  vtrej003_lab11_part3.c
  Author : Vincent
  Partner 1 Name & E-mail: Briana Ortega Vazquez borte012@ucr.edu
  Lab Section: 021
  Assignment: Lab #11 Exercise #3
  Exercise Description:

  I acknowledge all content contained herein, excluding template or example
  code, is my own original work.
*/
#include <avr/io.h>
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"
#include "bit.h"

unsigned char tmpC = 0x00;
static unsigned char c = 0;
unsigned char s[16] = {'h','e','l','l','o'};
enum SM_Task {SM_output};

int SM_TaskTick(int state){
	unsigned char x = 0;
	x = GetKeypadKey();
	if(c >16)
		c = 0;
	switch(state){
		case SM_output:
			switch(x){
				case '\0':
					//If I want to include part 1
					//tmpC = 0x1F;
					break;
				case '1':
					tmpC = 0x01;
                                        s[c] = (tmpC +'0');
					LCD_DisplayString(0,s);
				//	c++;
					//LCD_Cursor(c);
					//LCD_WriteData(tmpC + '0');
					break;
				case '2':
					tmpC = 0x02;
s[c] = (tmpC +'0');

				        LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '3':
					tmpC = 0x03;
s[c] = (tmpC +'0');

					LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '4':
					tmpC = 0x04;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '5':
					tmpC = 0x05;
s[c] = (tmpC +'0');

					LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '6':
					tmpC = 0x06;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '7':
					tmpC = 0x07;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '8':
					tmpC = 0x08;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case '9':
					tmpC = 0x09;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + '0');
					break;
				case 'A':
					tmpC = 0x0A;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + 0x37);
					break;
				case 'B':
					tmpC = 0x0B;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + 0x37);
					break;
				case 'C':
					tmpC = 0x0C;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + 0x37);
					break;
				case 'D':
					tmpC = 0x0D;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + 0x37);
					break;
				case '*':
					tmpC = 0x0E;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
				//	LCD_WriteData(tmpC + 0x1C);
					break;
				case '0':
					tmpC = 0x00;
s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

				//	LCD_Cursor(c);
					//LCD_WriteData(tmpC + '0');
					break;
				case '#':
					tmpC = 0x0F;
					s[c] = (tmpC +'0');

LCD_DisplayString(0,s);

					//LCD_Cursor(c);
					//LCD_WriteData(tmpC + 0x14);
					break;
				default:
					//tmpC = 0x1B;
					//LCD_DisplayString(0,s);

					//LCD_Cursor(c);
					//LCD_WriteData(tmpC + '0');
					break;
			}

                                       
					c++;
			state = SM_output;
			
			// Wasn't part of lab but since I had the LEDs on port B and LCD on Port C
			// any input is shown by LCD and LEDs
			PORTB = tmpC;
			PORTC = tmpC;
			break;
	}
	return state;
}

int main(void)
{
    DDRA = 0xF0; PORTA = 0x0F; 
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long int SM_TaskTick_time = 10;
	unsigned long int tmpGCD = 1;
	unsigned long int GCD = tmpGCD;
	unsigned long int SM_Task_period = SM_TaskTick_time/GCD;
	
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = 0;
	task1.period = SM_Task_period;
	task1.elapsedTime = SM_Task_period;
	task1.TickFct = &SM_TaskTick;
	
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	LCD_ClearScreen();
	unsigned short i;
    while (1) {
		for (i = 0; i < numTasks; i++){
			if (tasks[i] ->elapsedTime == tasks[i] ->period ){
				tasks[i] ->state = tasks[i] ->TickFct(tasks[i] ->state);
				tasks[i] ->elapsedTime = 0;
			}
			tasks[i] ->elapsedTime += 1;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
  }
	return 0;
}
