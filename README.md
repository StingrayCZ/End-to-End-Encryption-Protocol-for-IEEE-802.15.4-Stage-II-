# Konzultace 27.7.2020

Jedná se u ukázkový prototyp, kde jednotlivé namísto **for cyklu** jsou jednotlivé iterace vytvořeny přímo v kódu. Tento kód pseudonáhodně generuje 2^12 číslo. Výstup je zobrazen na obrázku níže.

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


