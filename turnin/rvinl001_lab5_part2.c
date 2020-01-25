/*	Author: rvinl001
 *  Partner(s) Name: David Kecheung
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {init, Start, Inc, Dec, Both1, Both2, Release} States;

void tick(){
	switch (States)
	{
		case Start:
			States = init;
			break;
		
		case init:
			if ((PINA & 0x03) == 0x01)
			{
				States = Inc;
				break;
			}else if ((PINA & 0x03) == 0x02){
				States = Dec;
				break;
			}else{
				States = init;
				break;
			}
			
		case Inc:
			if ((PINA & 0x03) == 0x00 || (PINA & 0x03) == 0x01)
			{
				States = Inc;
				break;
			}else if ((PINA & 0x03) == 0x02 || (PINA & 0x03) == 0x03){
				States = Both1;
				break;
			}
			
		case Dec:
			if ((PINA & 0x03) == 0x00 || (PINA & 0x03) == 0x02)
			{
				States = Dec;
				break;
			}else if ((PINA & 0x03) == 0x01 || (PINA & 0x03) == 0x03){
				States = Both2;
				break;
			}
				
		case Both1:
			if ((PINA & 0x03) == 0x00 || (PINA & 0x03) == 0x01)
			{
				States = Release;
				break;
			}else if ((PINA & 0x03) == 0x02 || (PINA & 0x03) == 0x03){
				States = Both1;
				break;
			}
			
		case Both2:
			if ((PINA & 0x03) == 0x00 || (PINA & 0x03) == 0x02)
			{
				States = Release;
				break;
			}else if ((PINA & 0x03) == 0x01 || (PINA & 0x03) == 0x03){
				States = Both2;
				break;
			}
			
		case Release:
			if ((PINA & 0x03) == 0x00)
			{
				States = init;
				break;
			}else{
				States = Release;
				break;
			}
		
		default:
			break;
			
			
	}
	
	switch(States) {   // State actions
     case init:
        PORTC = 0x07;
        break;
     case Inc:
		PORTC = 0x09;
        break;
     case Dec:
        PORTC = 0x00;
        break;
     case Both1:
		PORTC = 0x00;
        break;
	 case Both2:
		PORTC = 0x00;
        break;
	case Release:
		PORTC = 0x00;
		break;
     default:
        break;
   } // State actions
	
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    States = Start;
	
    while (1) 
    {
		tick();
    }
}
