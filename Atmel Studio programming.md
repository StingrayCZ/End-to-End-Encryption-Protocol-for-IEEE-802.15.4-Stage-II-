This repository contain all codes what I have done in the Atmel Studio...

## GPIO (General Purpose Input Output)

```sh
/*
* GccApplication10.c
*
* Created: 03.05.2020 22:07:18
* Author : jarom
*/

#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
		
	DDRE|= (1 << 3);
	PORTE|=(1 << 3);
	
	DDRE|= (1 << 4);
	PORTE|=(1 << 4);
	
	DDRG|= (1 << 5);
	PORTG|=(1 << 5);
	
	DDRB|= (1 << 2);
	PORTB|=(1 << 2);
	
	DDRG|= (1 << 1);
	PORTG|=(1 << 1);
	
	DDRD|= (1 << 3);
	PORTD|=(1 << 3);
	
		
	/* Replace with your application code */
	while (1)
	{
		PORTG ^=(1 << 5);
		_delay_ms(50);
		
		PORTE ^=(1 << 3);
		_delay_ms(50);
		
		PORTE ^=(1 << 4);
		_delay_ms(50);
		
		PORTB ^=(1 << 2);
		_delay_ms(50);
		
		PORTG ^=(1 << 1);
		_delay_ms(50);
		
		PORTD ^=(1 << 3);
		_delay_ms(50);
	}

	return 0;
}


```
