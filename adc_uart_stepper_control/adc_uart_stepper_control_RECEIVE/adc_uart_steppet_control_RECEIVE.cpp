/*
 * adc_uart_stepper_control_RECEIVE.cpp
 *
 * Created: 1/26/2018 11:00:04 PM
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
	UCSRB = 1<<RXEN;
	UCSRC = 1<<URSEL | 1<<UPM1 | 1<<UPM0 | 1<<USBS | 1<<UCSZ1 | 1<<UCSZ0;//acessing UCSRC:ODD parity mode:2 stop bits:8-bit character size	
}
uint8_t usart_rece(void)
{
	while((UCSRA & 1<<RXC)==0);//WAIT UNTILL RECEIVING IS COMPLETE
	return UDR;
}

void stepper_clockwise_PORTD(void)
{
	PORTD = 0x0A;
	_delay_ms(50);
	PORTD = 0X06;
     _delay_ms(50);
	PORTD = 0X05;
     _delay_ms(50);
	PORTD = 0X09;
	_delay_ms(50);
}
void stepper_anticlockwise_PORTD(void)
{
	PORTD = 0x09;
    _delay_ms(50);
	PORTD = 0x05;
    _delay_ms(50);
	PORTD = 0x06;
    _delay_ms(50);
	PORTD = 0x0A;
	_delay_ms(50);	
}
void stepper_hold_PORTD(void)
{
	PORTD = 0xFF;
	_delay_ms(50);
}

int main(void)
{
	uint8_t arm_value1;
	DDRD = 0XFF;
	PORTD = 0XFF;
	usart_init();
    /* Replace with your application code */
    while (1) 
    {
		//stepper motor1 control
		arm_value1 = usart_rece();
		if (arm_value1 == 0x06) //joystick is left
		{
			stepper_anticlockwise_PORTD();
		}
		else if(arm_value1 == 0x07)//if joystick is right
		{
			stepper_clockwise_PORTD();
		}
		else
		{
			stepper_hold_PORTD(); //ARM_VALUE = 0X08 : HOLD STEPPER MOTOR 1
		}
		_delay_ms(20);		
    }
}

