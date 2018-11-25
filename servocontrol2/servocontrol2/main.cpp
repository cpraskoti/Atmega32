/*
 * servocontrol2.cpp
 *
 * Created: 12/24/2017 3:36:42 PM
 * Author : chandra prakash
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>





int main(void)
{
	DDRD |=  1<<PIND5;
	
	TCCR1A |= 1<<COM1A1 | 1<<WGM11;//non -inverting mode and wgm mode: icr1 as top and 00 as Bottom
	TCCR1B |=1<<WGM12 | 1<<WGM13 | 1<<CS10 | 1<<CS11 ;//64 prescaLing
	ICR1 = 4999 ;
	
    /* Replace with your application code */
   
		while(1)
		{	
         for(int i = 140 ; i<=630 ; i+=5)
		 {
			 OCR1A = i;
			 _delay_ms(100);
		 }
		 

		}	
   
}

