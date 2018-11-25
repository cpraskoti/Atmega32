/*
 * adc_from_joystick_led_out.cpp
 *
 * Created: 1/21/2018 6:19:50 PM
 * Author : chandra prakash
 */ 

/*
 * JoystickModule.cpp
 *
 * Created: 12/11/2017 9:43:24 PM
 * Author : chandra prakash
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

//enable ADC
void adc_init(void)
{
	ADMUX |= 1<<REFS0;//AVCC as VREF
	ADCSRA |= 1<<ADEN | 1<<ADPS0 | 1<<ADPS1;//PRESCALING 8 FOR 125KhZ AND ADC ENABLE
}

//read analog value from ADC0 and then converts to 10 bit digital
uint16_t analog_read_ADC0(void)
{
			//READING ADC0
                uint16_t result;
				ADCSRA |=1<<ADSC;//START CONVERSION
				while(ADCSRA & 1<<ADSC);//WAIT UNTIL CONVERSION
				result = ADC;
				return (result);    
			    ADC = 0;
				result = 0;
}
uint16_t analog_read_ADC1(void)
{
	uint16_t result;
	ADMUX |= 1<<MUX0 ;
	ADCSRA |=1<<ADSC;//START CONVERSION
	while(ADCSRA & 1<<ADSC);//WAIT UNTIL CONVERSION
	result = ADC;
	return (result);
	ADC = 0;
	result = 0;
}

int main(void)
{
	uint16_t result1;
	uint16_t result2;
	
	DDRA = 0X00;
	DDRB = 0XFF;
	DDRC = 0x00;
	DDRD = 0x00;
	PORTB = 0X00;
	adc_init();
    while (1) 
    {
		            result1 = analog_read_ADC0() ;
		            if(result1 < 462)
		            {
			            PORTB = 1<<PINB0;
		            }
		            else if(result1 > 700)
		            {
			            PORTB = 1<<PINB2;
		            }
		            else
		            {
			            PORTB = 1<<PINB1;
		            }
		            result1 = 0x00;
		           
					result2 = analog_read_ADC1();
							 if (result2 < 462)
							 {
								 PORTB |= 1<<PINB3;	
							 }
							 else if (result2 > 700)
							 {
								 PORTB |= 1<<PINB5;	 
							 }
							 else
							 {
							     PORTB |= 1<<PINB4;	
							 }
							 result2 = 0x00;					 
			          	  	
				
				 ADMUX &= 1<<REFS0;
				 /* let me tell something about this line. This fucking busllshit pussy line destroyed my whole 3 days.
				  without this shit, the program always called ADC0 channel for only one time and then always ADC1 .
				  And i was so fucckkeeed,,,This was due to change in admux value from channel adc0 to adc1 and remained always adc1. 
				  Finally i realized that loophole and it was my turn to fuck that pusssssyyyyhhhhooooooo000000leeee.
				  I put my dick in that pussy so hard and rubbed the dick at very very high frequency that bloody pussy hole is so 
				  fuuuucccckkkkkkeeeeeeedddddd now.Its bleeding,,,i took my revenge,,that pussy is never gonna dare to think about my dick . 
				  Ahhhhh,,,Ahhhhhh,,,mAJJA AYO  relimai,, 
				   */
											   
      }
}

