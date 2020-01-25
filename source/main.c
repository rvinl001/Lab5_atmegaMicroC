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


enum States {init, Start, Inc, Dec, Hold1, Hold2, Release, Both} States;
unsigned char ctr = 0x07;
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
			}else if (PINA == 0x00){
				States = init;
				break;
			}
			
		case Inc:
			if ((PINA & 0x03) == 0x01)
			{
				States = Hold1;
				break;
			}else if ((PINA & 0x03) == 0x03){
				States = Both;
				break;
			}
			else if (PINA == 0x00)
			{
				States = init;
			}
			
		case Dec:
			if ((PINA & 0x03) == 0x02)
			{
				States = Hold2;
				break;
			}else if ((PINA & 0x03) == 0x03){
				States = Both;
				break;
			}
			else if (PINA = 0x00)
			{
				States = init;
			}
		case Hold1:
			if (PINA == 0x01){
				States = Hold1;
				break;
			}
			else if (PINA == 0x00){
				States = Release;
				break;
			}
			else if (PINA == 0x03) {
				States = Both;
				break;
			}
                case Hold2:
                        if (PINA == 0x02){
                                States = Hold2;
                                break;
                        }
                        else if (PINA == 0x00){
                                States = Release;
                                break;
                        }
			else if (PINA == 0x03) {
				States = Both;
				break;
			}

		case Release:
			if ((PINA & 0x03) == 0x01)
			{
				States = Inc;
				break;
			}else if (PINA == 0x02){
				States = Dec;
				break;
			}
			else if (PINA == 0x03){
				States = Both;
				break;
			}
		case Both:
			break;
		default:
			break;
			
			
	}
	
	switch(States) {   // State actions
     	case init:
        	ctr = 0x07;
       	 	break;
     	case Inc:
		if (ctr < 9)
			ctr++;
        	break;
     	case Dec:
        	if (ctr > 0)
			ctr--;
        	break;
	case Hold1:
		break;
	case Hold2:
		break;
	case Release:
		break;
	case Both:
		ctr = 0;
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
    ctr = 0x07;	
    while (1) 
    {
	tick();
	PORTC = ctr;	
    }
}
