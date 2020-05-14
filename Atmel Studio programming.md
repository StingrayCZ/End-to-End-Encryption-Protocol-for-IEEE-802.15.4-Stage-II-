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

## GPIO - Bitové operace a makra

```sh 
// Assignment Operators

&=	Bitwise AND assignment operator.	        C &= 2 is same as C = C & 2
^=	Bitwise exclusive OR and assignment operator.	C ^= 2 is same as C = C ^ 2
|=	Bitwise inclusive OR and assignment operator.	C |= 2 is same as C = C | 2
```


```sh
#define F_CPU 16000000   
#include <avr/io.h>
#include <util/delay.h>

#define SETBIT(VAR, BIT) (VAR |= ( 1 << BIT ) )
#define CLEARBIT(VAR, BIT) (VAR &= ~(1 << BIT ) ) // SOUCIN + NEGACE
#define ISSET(VAR, BIT) (VAR & ( 1 << BIT ) )     // SOUCIN

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

## GPIO (pokročilejší header)

### Main.c
```sh
#define F_CPU 16000000   
#include <stdio.h>
#include <avr/io.h>
#include <avr/delay.h>

#include "Header.h"

int main(void)
{
    LED0DEF
	LED1DEF
	LED2DEF
	
	
    while (1) 
    {
		LED0ON
		_delay_ms(200);
		LED1ON
		_delay_ms(200);
		LED2ON
		_delay_ms(200);
		
		
		LED0OFF
		_delay_ms(200);
		
		LED1OFF
		_delay_ms(200);
		
		LED2OFF
		_delay_ms(200);
    }
}
```
### Header.c
```sh
#include <avr/io.h>

#ifndef MAKRA_H_
#define MAKRA_H_
//Bitove operace

#define sbi(var, mask)  ((var) |= (uint8_t)(1 << mask))     // Bitwise inclusive OR and assignment operator.   C |= 2 is same as C = C | 2
#define cbi(var, mask)  ((var) &= (uint8_t)~(1 << mask))    // Bitwise AND assignment operator.	               C &= 2 is same as C = C & 2
#define tbi(var,mask)	(var & (1 << mask) )
#define xbi(var,mask)	((var)^=(uint8_t)(1 << mask))       // Bitwise exclusive OR and assignment operator.   C ^= 2 is same as C = C ^ 2

//hardware
//#define LED0_PIN G,5
//#define LED1_PIN E,3
//#define LED3_PIN E,4

#define LED0DEF sbi(DDRG,5);
#define LED1DEF sbi(DDRE,3);
#define LED2DEF sbi(DDRE,4);


#define LED0ON sbi(PORTG,5);
#define LED1ON sbi(PORTE,3);
#define LED2ON sbi(PORTE,4);

#define LED0OFF xbi(PORTG,5);
#define LED1OFF xbi(PORTE,3);
#define LED2OFF xbi(PORTE,4);

#endif
```

## Power (own solution)
```sh
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int vysledek, cislo, mocnitel;

    printf("Zadej cislo:\n\r");
    scanf("%d", &cislo);

    printf("Zadej mocnictele:\n\r");
    scanf("%d", &mocnitel);


    vysledek = power(&cislo, &mocnitel);

    printf("\n\rCislo je %d", vysledek);

    return 0;
}


int power(int *num, int *power, int numpow)
{

    numpow = *num;

    for(int i = 1; i < *power; i++)
    {

        numpow *= *num;
    }

    return numpow;
}
```
