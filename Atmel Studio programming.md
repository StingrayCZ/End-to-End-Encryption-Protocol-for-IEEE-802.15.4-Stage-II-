This repository contain all codes what I have done in the Atmel Studio...

## GPIO (General Purpose Input Output)

```sh
˜  bitová negace<br/>
|  bitový součet<br/>
&  bitový součin<br/>
ˆ  bitová nonekvivalence<br/>
```

```sh
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

## GPIO (Second Excercise)

```sh
//#define F_CPU 16000000                 // dulezite
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/iom128rfa1.h >
//#define F_CPU 8000000UL // 8 MHz internal crystal



int main(void)
{
	DDRE|= (1 << 3);
	

	
	while(1)
	{
		PORTE |= (1 << 3);
		_delay_ms(200);
		
		PORTE &= ~(1 << 3);
		_delay_ms(200);		
		
	}
}

```

## GPIO (Excercise 3)

```sh
#define F_CPU 16000000   
#include <avr/io.h>
#include <util/delay.h>

#define SETBIT(VAR, BIT) (VAR |= ( 1 << BIT ) )
#define CLEARBIT(VAR, BIT) (VAR &= ~(1 << BIT ) ) // SOUCIN + NEGACE
#define ISSET(VAR, BIT) (VAR & ( 1 << BIT ) )

int main(void)
{

	
	SETBIT(DDRG, 5);
	SETBIT(DDRE, 3);
	SETBIT(DDRE, 4);
	
	
	/* Replace with your application code */
	while (1)
	{
			
		SETBIT(PORTG, 5);
		_delay_ms(200);
				
		SETBIT(PORTE, 3);
		_delay_ms(200);
		
		SETBIT(PORTE, 4);
		_delay_ms(200);
		
		CLEARBIT(PORTG, 5);
		_delay_ms(200);
					
		CLEARBIT(PORTE, 3);
		_delay_ms(200);
		
		CLEARBIT(PORTE, 4);
		_delay_ms(200);
		
		
		SETBIT(PORTE, 4);
		_delay_ms(200);
		
		SETBIT(PORTE, 3);
		_delay_ms(200);
		
		SETBIT(PORTG, 5);
		_delay_ms(200);
		
		
				
		CLEARBIT(PORTE, 4);
		_delay_ms(200);
		
		CLEARBIT(PORTE, 3);
		_delay_ms(200);
		
		CLEARBIT(PORTG, 5);
		_delay_ms(200);

			
	}
}

```
