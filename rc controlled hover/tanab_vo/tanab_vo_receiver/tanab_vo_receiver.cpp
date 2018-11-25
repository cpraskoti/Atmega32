/*
 * tanab_vo_receiver.cpp
 *
 * Created: 1/30/2018 5:40:12 PM
 * Author : chandra prakash
 */ 

#define F_CPU 1000000UL
#define BAUDRATE 9600
#define UBRR_VALUE (F_CPU/(16UL*BAUDRATE)-1)
#include <avr/io.h>
#include <util/delay.h>
unsigned char value;
//(NOTE: BE CAREFUL THAT uint8_t HOLDS ONLY 8 BIT DATA AND DONT USE THIS TYPE FOR VARIABLE THAT HOLDS DATA OF 10-BIT DIGITAL O/P )
void usart_init(void)
{
	UBRRH = UBRR_VALUE >>8;
	UBRRL = UBRR_VALUE;
	UCSRB = 1<<RXEN | 1<<TXEN ;
	UCSRC = 1<<URSEL | 1<<UPM1 | 1<<UPM0 | 1<<USBS | 1<<UCSZ1 | 1<<UCSZ0;//acessing UCSRC:ODD parity mode:2 stop bits:8-bit character size
}
uint8_t usart_rece(void)
{
	while((UCSRA & 1<<RXC)==0);//WAIT UNTILL RECEIVING IS COMPLETE
	value = UDR;
	UDR = 0x00;
	return value;
}
void stepper_clockwise_PORTD(void)
{
	PORTD = 0xA0;
	_delay_ms(5);
	PORTD = 0X60;
	_delay_ms(5);
	PORTD = 0X50;
	_delay_ms(5);
	PORTD = 0X90;
	_delay_ms(5);
}
void stepper_anticlockwise_PORTD(void)
{
	PORTD = 0x90;
	_delay_ms(5);
	PORTD = 0x50;
	_delay_ms(5);
	PORTD = 0x60;
	_delay_ms(5);
	PORTD = 0xA0;
	_delay_ms(5);
}
void stepper_hold_PORTD(void)
{
	PORTD = 0xFF;
	_delay_ms(20);
}
void stepper_clockwise_PORTC(void)
{
	PORTC = 0x0A;
	_delay_ms(5);
	PORTC = 0X06;
	_delay_ms(5);
	PORTC = 0X05;
	_delay_ms(5);
	PORTC = 0X09;
	_delay_ms(5);
	
}
void stepper_anticlockwise_PORTC(void)
{
	PORTC = 0x09;
	_delay_ms(5);
	PORTC = 0x05;
	_delay_ms(5);
	PORTC = 0x06;
	_delay_ms(5);
	PORTC = 0x0A;
	_delay_ms(5);
}
void stepper_hold_PORTC(void)
{
	PORTC = 0xFF;
	_delay_ms(20);
}
int main(void)
{
    uint8_t arm_value1 ;
    uint8_t arm_value2 ;
    uint8_t wheel_value;
    uint8_t message;
	
    DDRB  = 0XFF;
    PORTB = 0x00;
    DDRD  = 0xFF;
    PORTD = 0X00;
    DDRC  = 0XFF;
    PORTC = 0X00;
    usart_init();
    while (1) 
    {
		message = usart_rece();
		wheel_value = message & 0x07;
		
	//	arm_value2 = message & 0X60;
	//	arm_value2 = arm_value2 >> 5;
		
		//wheel control
		if(wheel_value == 0x01)
		{
			PORTB = 0X0A;//BACKWARD
		}
		else if(wheel_value == 0x02)
		{
			PORTB = 0X05;//forward
		}
		else if (wheel_value == 0x03)
		{
			PORTB = 0x06;//left
		}
		else if (wheel_value == 0x04)
		{
			PORTB = 0x09;//right
		}
		else
		{
			PORTB = 0xFF;//stop	wheel_value= 0x05
		}
		
		//stepper1 control
		arm_value2 = message & 0X60;
		arm_value2 = arm_value2 >> 5;
		arm_value1 = message & 0x18;
		arm_value1 = arm_value1 >> 3;
		if (arm_value1 == 0x01)
		{
			stepper_anticlockwise_PORTD();
		}
		else if (arm_value1 == 0x02 )
		{
			stepper_clockwise_PORTD();
		}
		else
		{
			stepper_hold_PORTD();
		}
		//stepper2 control
		if (arm_value2 == 0x01)
		{
			stepper_anticlockwise_PORTC();
		}
		else if (arm_value2 == 0x02 )
		{
			stepper_clockwise_PORTC();
		}
		else
		{
			stepper_hold_PORTC();
		}
		
    }
}

