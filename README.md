# Konzultace 3.7.2020

Pokus o kompilaci BigN ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/BigN%20lib.zip">zde</a>. </a>  </p>

<p float="left">
  <img src="/Pictures (general)/Errata.PNG" width="800" /> 
<p float="left"> </p> 

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


