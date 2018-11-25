/*
 * GccApplication4.cpp
 *
 * Created: 11/27/2017 9:38:16 AM
 * Author : chandra prakash
 */ 

   
   #include <avr/io.h>


   int main(void)
   {
	   int result;
	   DDRB = 0X01;
	   
	   PORTB =0X01;
	   ADCSRA |=1>>ADPS0|1>>ADPS1|0>>ADPS2;
	   ADMUX |=0b01000000;
	   ADMUX &=0b01111111;
	   ADMUX &=0b11100000;
	   
	   
	   /* Replace with your application code */
	   while (1)
	   {
		   ADCSRA |=0b10000000;
		   ADCSRA |=0b01000000;
		   while(ADCSRA & 1 << ADSC);
		   result = ADCW;
		   if(result>512)
		   {
			   PORTB &=0xFE;
		   }
		   else
		   {
			   PORTB |=0x01;
		   }

	   }
   }

