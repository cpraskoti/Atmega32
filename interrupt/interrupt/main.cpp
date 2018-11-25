/*
 * interrupt.cpp
 *
 * Created: 12/4/2017 3:19:33 PM
 * Author : chandra prakash
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 ISR(TIMER1_COMPA_vect)
{
PORTB ^= 1<<PINB0 | 1<<PINB1;
}


int main(void)
{
	sei();
	DDRB = 0X3;
	PORTB |= 1<<PINB0 | 1<<PINB1;
	TCCR1A |= 0<<COM1A1 | 0<<COM1A0 | 0<<WGM13 | 0<<WGM12 | 0<<WGM11 | 0<<WGM10;
	TCCR1B |= 1<<CS12 | 0<<CS11 | 0<<CS10 ;
	TIMSK = 1<<OCIE1A;
	TCNT1 = 0;
	OCR1A = 20000;
	
	
	
    /* Replace with your application code */
    while (1) 
    {
			
    }
}

