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

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    
	unsigned char tempA = 0x00;

	while (1) {
	tempA = PINA & 0xFF;
		
		if(tempA < 0x01)
		{
			PORTC = 0x40;
		}
		else if (tempA < 0x03)
		{
			PORTC = 0x60;
		}
		else if (tempA < 0x05)
		{
			PORTC = 0x70;
		}
		else if (tempA < 0x07)
		{
			PORTC = 0x38;
		}
		else if (tempA < 0x0A)
		{
			PORTC = 0x3C;
		}
		else if (tempA < 0x0D)
		{
			PORTC = 0x3E;
		}
		else
		{
			PORTC = 0x3F;
		}
	
    	}
    return 1;
}
