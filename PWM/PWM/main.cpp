/*
 * PWM.cpp
 *
 * Created: 11/29/2017 9:05:00 AM
 * Author : chandra prakash
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |=1<<PINB3;
	TCCR0 = 1<<WGM00 | 1<<CS02 | 1<<CS00 | 1<<COM01;
	int count;	
    /* Replace with your application code */
    while (1) 
    {	
		for(count=0;count<=120;count++)
		{
		    OCR0 = count;
			_delay_ms(2);				
		}
		for(count=120;count>=0;count--)
		{
			OCR0 = count;
			_delay_ms(2);	
		}
    }
}

