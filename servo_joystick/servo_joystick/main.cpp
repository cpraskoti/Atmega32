/*
 * servo_joystick.cpp
 *
 * Created: 12/25/2017 2:52:07 PM
 * Author : chandra prakash
 */
#define F_CPU 16000000UL 
#include <util/delay.h>
#include <avr/io.h>

//16-bit counter PWM initailaizaion

void counter_init(void)
{
	TCCR1A |= 1<<COM1A1 | 1<<WGM11;//non -inverting mode and wgm mode: icr1 as top and 00 as Bottom
    TCCR1B |=1<<WGM12 | 1<<WGM13 | 1<<CS10 | 1<<CS11 ;//64 prescaLing
    ICR1 = 4999 ;
}
void adc_init(void)
{
	ADMUX |= 1<<REFS0;//AVCC as VREF
	ADMUX |= 1<<MUX0 | 1<<MUX1 | 1<<MUX2;//ADC7 AS ANALOG INPUT
	ADCSRA |= 1<<ADEN | 1<<ADPS0 | 1<<ADPS1 | 1<<ADPS2;//PRESCALING 128 FOR 125KhZ AND ADC ENABLE
}
int return_adcvalue(void)
{
	ADCSRA |=1<<ADSC;
	while(ADCSRA & (1<<ADSC));
	int value = ADCW;
	return(value);
}
int main(void)
{
	DDRD = 0XFF;
	DDRA = 0x00;
	PORTD = 0x00;
	
	counter_init();
    /* Replace with your application code */
    while (1) 
    {
		
		float value;
		float calculation;
		
		ADCSRA |=1<<ADSC;
		while(ADCSRA & (1<<ADSC));
		 value = ADCW;
		 calculation = 0.439*value;// ocr1a - 140 =((640-140)/(1024-0))*value : but dont use that : use 500/1024 = 0.488 but also
		                           //used 450/1024= 0.439 for realtime preciseness otherwise there is problem in type casting:
         OCR1A = calculation + 140  ;
		
    }
}

