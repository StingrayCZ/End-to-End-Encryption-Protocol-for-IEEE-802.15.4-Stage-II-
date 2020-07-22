# Konzultace 23.7.2020
## Test prvočíselnosti

### Utility function to do modular exponentiation. 
```C
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int x, y, p;
    x = 174;
    y = 110;
    p = 221;


    int result = power(x, y, p);

    printf("%d", result);

}


int power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

```


# Konzultace 20.7.2020

## Fáze generování 32 bitového čísla - dosazeni vetsiho cisla nez nabizi rand()

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int randNUM, SUM;

    srand((unsigned int) time(NULL));

    for(int i = 0; i < 128; i ++){

            randNUM = (rand()*rand()*rand());           // dosazeni vetsiho cisla
            printf("%d\n\r", randNUM);

            SUM += randNUM;
    }

    printf("%d\n\r",SUM);


    return 0;
}
```

## Násobení pomocí bitových operací
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j, i;

    j = 80;

    i = (j << 6) + (j << 4);    // vysledek je 6400

    printf("Cislo je %d", i);

    return 0;
}
```

## Spojení jednotlivých 32bit stringu do 512 stringu - metodika
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    int length;


    char pp [] = "57";
    char pq [] = "348";

    strcat(pp, pq);

    printf("%s\n", pq);

    length = strlen(pp);

    printf("Result is %d", length);


    return 0;
}
```

## Metodika spojovani (jde to  jinak než pomocí for?)
```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY_LINE printf("\n");

int main()
{


    uint8_t randNUM, SUM;
    char buffer[10];
    char BigN[] = "0";

    srand((unsigned int) time(NULL));

    for(int i = 0; i < 8; i ++)                // 8 X 4 bit cislo = 32 bitove cislo
    {

        SUM = rand() % 16;                     // pseudorandomni cislo o 4 bitove delce
        printf("DEC = %d\n\r",SUM);            // ukazka pseudorandomniho cisla o 4 bitove delce

        itoa(SUM,buffer,2);                    // prevedeni do binarni soustavy

        printf("BIN = %s\n", buffer);          // ukazka cisla jako stringu

        strcat(BigN, buffer);                  // spojeni aktualniho vysledku s predchozim - postupne nabalovani

        EMPTY_LINE


    }

    printf("TOTAL = %s\n", BigN);             // vypis 32 bitoveho cisla


    return 0;
}
```
