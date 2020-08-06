# Konzultace 6.8.2020

<p float="left">
  <img src="/Pictures (general)/FlowCH Phase A.png" width="300" /> 
<p float="left"> </p>

## Rand funkce

<p float="left">
  <img src="/Pictures (general)/RandPic.PNG" width="400" /> 
<p float="left"> </p> 

```C
BIGD  a, n;
	
	a = bdNew();
	n = bdNew();
	
	bdSetShort(n, 25);
	
	size_t bdRandomNumber (a, n);
	
	bdPrintHex("RAND HEX je 0x ", a, "\n\r");
	bdPrintDecimal("RAND DEC je ", a, "\n\r");
	
	bdFree(&a);
	bdFree(&n);
```

## Fermat
```C

BIGD TESTNUM, vysledek;
	
	TESTNUM = bdNew();
	vysledek = bdNew();
	
	bdSetShort(TESTNUM, 17);
	//bdConvFromHex(TESTNUM, "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000004b");
	
	//printf("testovaci cislo je %d\n\r", TESTNUM);
	bdPrintDecimal("testovaci cislo je ", TESTNUM, "\n\r");


	bdSetShort(vysledek, fermat_test(TESTNUM));
	
	bdPrintDecimal("Vysledek Fermat testu ", vysledek, "\n\r");
		
	
	bdFree(&TESTNUM);
	bdFree(&vysledek);	
```

## bdPower
<p float="left">
  <img src="/Pictures (general)/dbPower.PNG" width="400" /> 
<p float="left"> </p> 
```C
BIGD CisloA, CisloB, CisloC;
		
		CisloA = bdNew();
		CisloB = bdNew();
		CisloC = bdNew();		
		
			
		bdSetShort(CisloB, 25);
		bdSetShort(CisloC, 5);
		
		//bdPower(CisloA, CisloB, CisloC);          //  y = g^n (up to available memory!) 
		bdMultiply(CisloA, CisloB, CisloC);     //  w = u * v. 
		
		bdPrintHex("Test Modulo HEX je 0x ", CisloA, "\n\r");
		bdPrintDecimal("Test Modulo DEC je ", CisloA, "\n\r");
		
		
		bdFree(&CisloA);
		bdFree(&CisloB);
		bdFree(&CisloC);	
```

## Původní kód
```C
// int TheFirstPoint(BIGD MOD, BIGD A, BIGD B, BIGD Xfirst, BIGD Yfirst, BIGD OrderG)
void TheFirstPoint(int *MOD, int *A, int *B, int *Xfirst, int *Yfirst, int *OrderG)
{  
        // Jak zmeni toto pole?
	int modulus, a, b;
	int poleA[1000];
	int poleB[1000];

	modulus = *MOD;
	a = *A;
	b = *B;

	// Application XPart
	YPart (&modulus, poleA);
	
	// Application YPart
	XPart(&modulus, &a, &b, poleB);

	// Iterations
	int X_iter = modulus - 1;
	int Y_iter = ((modulus - 1) / 2) + 1;
	
	// Computing order
	int order = 0;
	
	#ifdef PRINT_ON
	// Point64_ts
	int x, y, y_neg;
	#endif // PRINT_ON

	for(int k = 0; k <= X_iter; k++)  // Give X's
	{
		for(int i = 0; i <= Y_iter; i++)  // Give Y's
		{
			if (poleA[i] == poleB[k])
			{
				if(order == 0)
				{

					*Xfirst = k;
					*Yfirst = i;
				}
				
				#ifdef PRINT_ON
				x = k;
				y = i;
				y_neg = modulus - i;
				
				
				printf("Yes, this number is in array\n\r");
				printf("Jedna se o cisla %d a %d\n\r", poleA[i], poleB[k]);
				EMPTYLINE
				printf("Coordinates are [%4d,%4d] [%4d,%4d] \n\r", x, y, x, y_neg);
				#endif // PRINT_ON

				order++;

			}
		}

	}

	order *= 2;
	order += 1;

	*OrderG = order;
}
```

```C
void checkValAB(int64_t *mod, int64_t *A, int64_t *B, int64_t *TESTvalue)
{
	int64_t a, b, compute, mocnitelA, mocnitelB, MOD;

	MOD = *mod;
	a = *A;
	b = *B;

	if(a == MOD)
	{

		*TESTvalue = 2;
	}

	else if(b == MOD)
	{

		*TESTvalue = 2;
	}

	else
	{
		mocnitelA = 3;
		mocnitelB = 2;

		compute =  4 * (power(&a, &mocnitelA)) + 27 * (power(&b, &mocnitelB));
		compute = modulo(&a, &MOD);
		
		if (compute > 0)
		{
			*TESTvalue = 1;
			
		}
		else
		{
			*TESTvalue = 2;
		}
		

	}
}
```

# Konzultace 5.8.2020

## bdModSquare (bigd.c)
```C
	 //int bdModSquare(BIGD a, BIGD x, BIGD m)
	 //Computes a = x^2 mod m
	 
	 int NumA, NumB, NumC;
	 
	 NumB = 36;
	 NumC = 5;
	 
	 bdModSquare(NumA, NumB, NumC);
	 
	 printf("Vysledek je %d", NumA);
```

```C
/** Computes a = x^2 mod m */
int bdModSquare(BIGD a, BIGD x, BIGD m)
{
	size_t n;
	int status;

	assert(a && x && m);
	/* Make sure all variables are the same size */
	n = max(x->ndigits, m->ndigits);

	bd_resize(a, n);
	bd_resize(x, n);
	bd_resize(m, n);

	/* Do the business */
	status = mpModSquare(a->digits, x->digits, m->digits, n);

	a->ndigits = mpSizeof(a->digits, n);

	return status;
}
```

## Test prvočísla
```C
	int TESTNUM = 2;
	printf("testovaci cislo je %d\n\r", TESTNUM);
	for(int iss = 0; iss < 10; iss++){
	int vysledek = fermat_test(&TESTNUM);
	printf("Vysledek testu je %d\n\r", vysledek);
	}
```

<p float="left">
  <img src="/Pictures (general)/Putty0508.PNG" width="800" /> 
<p float="left"> </p> 


## Test flashnutí desek
U jedné desky blikají ledky pomaleji. I přesto, že jsem paměti pročistil (Erase) a nahrál stejný program na obě desky. **Může to ovlivnit nějak běh aplikace?**

```C
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRE |= (1<<PE3);   // operace bitovy OR  |=
	DDRE |= (1<<PE4);   // operace bitovy OR  |=
	DDRG |= (1<<PG5);   // operace bitovy OR  |=
	
	

	while (1)
	{
		PORTG |= (1<<PG5);
		_delay_ms(100);
		
		PORTE |= (1<<PB3);       // operace bitovy OR  |=
		_delay_ms(100);

		
		PORTE |= (1<<PB4);
		_delay_ms(100);
		
			
		PORTG &= ~(1<<PG5);
		_delay_ms(100);
		
		PORTE &= ~(1<<PB3);     // operace bitovy AND  &=  ~ negace jednicky
		_delay_ms(100);
		
		PORTE &= ~(1<<PB4);
		_delay_ms(100);
		
	}
}

```

# Konzultace 3.7.2020

Pokus o kompilaci BigN ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/BigN%20lib.zip">zde</a>. </a>  </p>

<p float="left">
  <img src="/Pictures (general)/Errata.PNG" width="800" /> 
<p float="left"> </p> 


### Alg. pro spojovani bitů
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTYLINE printf("\n");

int main()
{

    srand((unsigned int) time(NULL));

    int Array[513];

    int round = 4;
    int BitLen;
    char buffer [513];


    printf("Enter Bit Lenght (1 = 1111):\n");
    scanf("%d", &BitLen);
    EMPTYLINE


    BitLen -= 1;


    Array[0] = 15;                   // Testovaci hodnota 15 MAX
//    Array[0] = rand() % 16;

    itoa (Array[0],buffer,2);

    printf("Round: 2^%d\n", round);
    printf("DEC rand: %d\n", Array[0]);
    printf("BIN rand: %s\n", buffer);
    EMPTYLINE
    for(int j = 1; j <= BitLen; j++)
    {

        Array[j] = Array[(j-1)] + (15 << round);                   // Testovaci hodnota 15 MAX
//        Array[j] = Array[(j-1)] + ((rand() % 16) << round);

        itoa (Array[j],buffer,2);


        round += 4;

        printf("Round: 2^%d\n", round);
        printf("DEC rand: %d\n", Array[j]);
        printf("BIN rand: %s\n", buffer);
        EMPTYLINE


    }



    EMPTYLINE
    printf("TOTAL DEC: %d\n", Array[BitLen]);
    itoa (Array[BitLen],buffer,2);
    printf ("TOTAL BIN: %s\n",buffer);

    return 0;
}
```

<p float="left">
  <img src="/Pictures (general)/OknoBits.PNG" width="800" /> 
<p float="left"> </p> 


### Ukazatel může být v jazyce C přetypován na specifický typ
```C
#include <stdio.h>
#include <stdlib.h>

int main()
{

//    int * pole = malloc(10 * sizeof(int));            // bez přetypování v jazyce C
    int * pole = (int *) malloc(10 * sizeof(int));      // s přetypování v jazyce C

    pole[0] = 12;
    pole[1] = 5;
    pole[2] = 2;

    for(int i = 0; i < 3; i++)
    {

        printf("Cislo je %d\n", pole[i]);
    }

    free(pole);  

    return 0;
}
```
### Maxima

**4 bit**  => 0-15   1111 (4x) </br>
**8 bit**  => 0-255  1111 1111 (8x) </br>
**16 bit** => 0-65535  1111 1111 1111 1111 (16x)  </br>
**32 bit** => 0-4294967295 1111 1111 1111 1111 1111 1111 1111 1111 (32x) </br>

### Velikosti jednolivých typů

<p float="left">
  <img src="/Pictures (general)/Typerange.PNG" width="800" /> 
<p float="left"> </p> 

### Funkce <stlib.h>
**calloc** - alokace dynamické paměti pro pole objektů </br>
**malloc** - alokace bloku dynamické paměti </br>
**realloc** - změna velikosti bloku dynamické paměti </br>
**free** - uvolnění dynamické paměti </br>
**sizeof** - velikost datoveho typu </br>



# Konzultace 27.7.2020

Jedná se u ukázkový prototyp algoritmu, kde jednotlivé iterace jsou vytvořeny přímo v kódu (namísto **for cyklu**). Tento kód pseudonáhodně generuje 2^12 číslo, které je složeno ze tří 2^4 čísel (viz obrázek níže). Výstup je zobrazen na obrázku pod kódem.

<p float="left">
  <img src="/Pictures (general)/MyThinkAdvance.PNG" width="800" /> 
<p float="left"> </p> 


**Otázka: Je tato myšlenka správná? Lze takto navýšením počtu iterací na 128, tj. 2^(4·128) => 2^(512) dosáhnout čísla o velikosti 512 bitů?**

Na zaslaný link jsem díval, zatím jsem jej nezkoušel kompilovat.

```c
#include <stdio.h>
#include <stdlib.h>
#define EMPTYLINE printf("\n");


int main()
{

    srand((unsigned int) time(NULL));

    int RandNUM;
    int resA, resB, resC, TOTAL;
    int num;
    char buffer [4];
    char bufferTOTAL [4];



    num = 0;

    printf("Davka %d\n", num);
    RandNUM = rand()%16;
    printf("Rand DEC %d\n", RandNUM);
    itoa (RandNUM,buffer,2);
    printf ("Rand BIN: %s\n",buffer);
    resA = RandNUM << num;


    EMPTYLINE

    num = 4;

    printf("Davka %d\n", num);
    RandNUM = rand()%16;
    printf("Rand DEC %d\n", RandNUM);
    itoa (RandNUM,buffer,2);
    printf ("Rand BIN: %s\n",buffer);
    resB = RandNUM << num;

    EMPTYLINE

    num = 8;

    printf("Davka %d\n", num);
    RandNUM = rand()%16;
    printf("Rand DEC %d\n", RandNUM);
    itoa (RandNUM,buffer,2);
    printf ("Rand BIN: %s\n",buffer);
    resC = RandNUM << num;


    EMPTYLINE

    TOTAL = resA + resB + resC;

    printf("TOTAL DEC %d\n", TOTAL);
    itoa (TOTAL,buffer,2);
    printf ("TOTAL BIN %s\n",buffer);

}

```

<p float="left">
  <img src="/Pictures (general)/CommandLine.PNG" width="800" /> 
<p float="left"> </p> 


