/*	Author: Abdirahman Abdi
 *  Partner(s) Name: N/A
 *	Lab Section:021
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 
 *	Demo link:
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
 TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet (unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
unsigned char flag = 0;
enum States {Start, firstLed, secLed, thirdLed, pause, restart} state;

void Tick() {
unsigned char press = ~PINA & 0x01;
 switch(state) {
   case Start:
   state = firstLed;   break;

   case firstLed:
   flag  = 0;
   if(press){
	   state = pause;
   }
   else{
	state = secLed;
   }
   break;

   case secLed:
   if(press){
           state = pause;
   }
   else if(flag == 0) {
           state = thirdLed;
   }
   else if(flag == 1) {
	   state = firstLed;
   }
   break;

   case thirdLed:
   flag = 1;
   if(press){
           state = pause;
   }
   else{
           state = secLed;
   }

   break;

   case pause:
   if(press){
	   state = pause;
   }else{
	   state = restart;
   }
   break;

   case restart:
   if(press){
	   state = Start;
   }

   break;

   default:
   	state = Start;
	break;
 }

 switch(state) {
   case Start:  break;

   case firstLed:
   PORTB = 0x01;
   break;

   case secLed:
   PORTB = 0x02;  break;

   case thirdLed:
   PORTB = 0x04;  break;

   case pause:
   break;

   case restart:
   break;



 }
}


int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    state = Start;
    TimerSet(300);
    TimerOn();
    while (1) {
    	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}