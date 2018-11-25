/*
 * 1sdelay.cpp
 *
 * Created: 12/12/2017 8:49:54 PM
 * Author : chandra prakash
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB =0XFF;
	PORTB =0X00;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0x01;
		_delay_ms(15);
		PORTB = 0x00; 
    }
}

