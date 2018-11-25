/*
 * adc_uart_stepper_control.cpp
 *
 * Created: 1/26/2018 10:50:22 PM
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

void arm_control_part(void)
{
	uint16_t adc_value2;
	uint16_t adc_value3;
	uint8_t digit;
	// stepper motor1 control part
	adc_value2 = analog_read_2();
	if (adc_value2 < 400)
	{
		digit = 0x06; //anticlockwise rotation of stepper moto1
		usart_trans(digit);
	}
	else if (adc_value2 > 700)
	{
		digit = 0x07;//clockwise rotation of stepper moto1
		usart_trans(digit);
	}
	else
	{
		digit = 0x08;//hold the motor
		usart_trans(digit);
	}
}
int main(void)
{
	DDRA = 0x00;
	usart_init();
	adc_enable();
    while (1) 
    {
		arm_control_part();
    }
}

