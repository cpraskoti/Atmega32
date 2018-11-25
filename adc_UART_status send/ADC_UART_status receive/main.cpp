/*
 * ADC_UART_status receive.cpp
 *
 * Created: 1/28/2018 4:54:40 PM
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
int main(void)
{
	uint8_t wheel_value;
	PORTB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		wheel_value = usart_rece();//assign THE RECEIVED VALUE FROM ANALOG READ PA0 to variable 'value'
		if(wheel_value == 0x01)
		{
			PORTB = 0XF1;//BACKWARD
		}
		else if(wheel_value == 0x02)
		{
			PORTB = 0XF2;//forward
		}
		else if (wheel_value == 0x03)
		{
			PORTB = 0xF3;//left
		}
		else if (wheel_value == 0x04)
		{
			PORTB = 0xF4;//right
		}
		else
		{
			PORTB = 0xF5;//stop	wheel_value= 0x05
		}
		_delay_ms(20);	
    }
}

