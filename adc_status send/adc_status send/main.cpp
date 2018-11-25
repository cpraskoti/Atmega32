/*
 * adc_status UART send.cpp
 *
 * Created: 1/28/2018 4:45:52 PM
 * Author : chandra prakash
 */ 

#define F_CPU 1000000UL
#define BAUDRATE 9600
#define UBRR_VALUE (F_CPU/(16*BAUDRATE)-1)
#include <avr/io.h>
#include <util/delay.h>

//(NOTE: BE CAREFUL THAT uint8_t HOLDS ONLY 8 BIT DATA AND DONT USE THIS TYPE FOR VARIABLE THAT HOLDS DATA OF 10-BIT DIGITAL O/P )
void usart_init(void)
{
	UBRRH = UBRR_VALUE >>8;
	UBRRL = UBRR_VALUE;
	UCSRB = 1<<TXEN;
	UCSRC = 1<<URSEL | 1<<UPM1 | 1<<UPM0 | 1<<USBS | 1<<UCSZ1 | 1<<UCSZ0;//acessing UCSRC:ODD parity mode:2 stop bits:8-bit character size
	
}
void usart_trans(uint8_t data)
{
	while((UCSRA & 1<<UDRE)==0);
	UDR = data;//UPLOAD THE SENDING DATA IN BUFFER
}
void adc_enable(void)
{
	ADCSRA = 1<<ADEN | 1<<ADPS1;//ADC PRESCALING 4 AND enable ADC
}
//read analog value from ADC0 and then converts to 10 bit digital
uint16_t analog_read_0(void)
{
	//READING ADC0
	uint16_t result;
	ADMUX = 1<<REFS0 ;
	ADCSRA |=1<<ADSC;//START CONVERSION
	while(ADCSRA & 1<<ADSC);//WAIT UNTIL CONVERSION
	result = ADCW;
	return result;
	ADCW = 0;
}
//READING ANALOG VALUE FROM ADC2
uint16_t analog_read_2(void)
{
	uint16_t result;
	
	ADMUX = 1 <<REFS0 | 0<<MUX0 | 1<<MUX1 | 0<<MUX2 | 0<<MUX3 | 0<<MUX4;
	ADCSRA |=1<<ADSC;//START CONVERSION
	while(ADCSRA & 1<<ADSC);//WAIT UNTIL CONVERSION
	result = ADCW;//converion from 10-bit to the 8 bit data
	return result;
	result = 0;
}

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		uint16_t adc_value0;
		uint16_t adc_value2;
		uint8_t digit;
		//wheel control part;
		adc_value0 = analog_read_0();
		// reads first from y-input and decide forward backward or if in mid position then checks x-input and decide left or right or to stop if x-input is also in mid position
		//backward
		if (adc_value0 < 400)
		{
			digit = 0x01;
			usart_trans(digit);
			PORTB = 0xF1;
		}
		//forward
		else if (adc_value0 > 700)
		{
			digit = 0x02;
			usart_trans(digit);
			PORTB = 0XF2;
		}
		else
		{
			adc_value2 = analog_read_2();
			//left or right or stop
			//left
			if (adc_value2 < 400)
			{
				digit = 0x03;
				usart_trans(digit);
				PORTB = 0XF3;
			}
			else if (adc_value2 > 700)
			{
				digit = 0x04;
				usart_trans(digit);
				PORTB = 0XF4;
			}
			//else stop
			else
			{
				digit = 0x05;
				usart_trans(digit);
				PORTB = 0XF5;
			}
		}
		_delay_ms(20);
    }
}


