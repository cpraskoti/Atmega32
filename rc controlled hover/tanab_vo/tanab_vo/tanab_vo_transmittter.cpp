/*
 * tanab_vo.cpp
 * 
 * Created: 1/30/2018 5:38:50 PM
 * Author : chandra prakash
 */ 

#define F_CPU 1000000UL     
#define BAUDRATE 9600
#define UBRR_VALUE (F_CPU/(16UL*BAUDRATE)-1)
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
//read analog value from ADC1
uint16_t analog_read_1(void)
{
	uint16_t result;
	ADMUX = 1<<REFS0 | 1<<MUX0 | 0<<MUX1 | 0<<MUX2 | 0<<MUX3 | 0<<MUX4;
	ADCSRA |=1<<ADSC;//START CONVERSION
	while(ADCSRA & 1<<ADSC);//WAIT UNTIL CONVERSION
	result = ADCW;//converion from 10-bit to the 8 bit data
	return result;
	result = 0;
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
//READING ANALOG VALUE FROM ADC3
uint16_t analog_read_3(void)
{
	uint16_t result;
	ADMUX = 1<<REFS0 | 1<<MUX0 | 1<<MUX1 | 0<<MUX2 | 0<<MUX3 | 0<<MUX4;
	ADCSRA |=1<<ADSC;//START CONVERSION
	while(ADCSRA & 1<<ADSC);//WAIT UNTIL CONVERSION
	result = ADCW;//converion from 10-bit to the 8 bit data
	return result;
	result = 0;
}

int main(void)
{
	uint16_t adc_value0;
	uint16_t adc_value1;
	uint16_t adc_value2;
	uint16_t adc_value3;
	
	uint8_t digit1;
	uint8_t digit2;
	uint8_t digit3;
	uint8_t message;
	
   
	DDRA = 0X00;
	usart_init();
	adc_enable();
    while (1) 
    {
		adc_value0 = analog_read_0();
		if (adc_value0 < 400)
		{
			digit1 = 0x01;
		}
		else if (adc_value0 > 700)
		{
			digit1 = 0x02;
		}
		else
		{
			adc_value1 = analog_read_1();
			if (adc_value1 < 400)
			{
				digit1 = 0x03;
			}
			else if (adc_value1 > 700)
			{
				digit1 = 0x04;
			}
			else
			{
				digit1 = 0x05;
			}
		}
		//adc for stepper 1
		adc_value2 = analog_read_2();
		if (adc_value2 < 400)
		{
			digit2 = 0x01;
		}
		else if (adc_value2 > 700)
		{
			digit2 = 0x02;
		}
		else
		{
			digit2 = 0x03;
		}
		//adc for stepper 2
		adc_value3 = analog_read_3();
		if(adc_value3 < 400)
		{
			digit3 = 0x01;
		}
		else if (adc_value3 > 700)
		{
			digit3 = 0x02;
		}
		else
		{
			digit3 = 0x03;
		}
		
		digit1 = digit1 | 0x18;	//digit1 = 0b0001 1digit1
		digit2 = digit2 << 3;   //digit2 = 0b000digit2 000
		digit2 = digit2 | 0x07; //digit2 = 0b000digit2 111
		digit2 = digit2 & digit1;//digit2 = 0b000digit2 digit1
        digit2 = digit2 | 0x60;  //digit2 = 0b011digit2 digit1
		
		digit3 = digit3 << 5;      //digit3 = 0b0digit30 0000
	    digit3 = digit3 | 0x1F;   //digit3 = 0b0digit31 1111
		message = digit3 & digit2;//message = 0b0digit3digit2 digit1
		
		usart_trans(message);
		
		 	
    }
}

