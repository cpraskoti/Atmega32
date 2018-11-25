/*
 * LEDBLINK2.cpp
 *
 * Created: 11/21/2017 12:42:11 PM
 * Author : chandra prakash
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB =1<<PINB0;
	
	/* Replace with your application code */
	while (1)
	{
		PORTB = 1<<PINB0;
		_delay_ms(1000);
		PORTB =0<<PINB0;
		_delay_ms(1000);
		
		
	}
}
