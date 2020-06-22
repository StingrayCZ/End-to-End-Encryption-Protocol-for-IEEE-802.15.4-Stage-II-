```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void primeTester();


int main()
{
    int64_t Num;
    int vysledek;

//    while(1)
//    {

        printf("\n****************************************");

        printf("\nNapis cislo k testovani\n");
        scanf("%d", &Num);

        primeTester(&Num, &vysledek);

          if(vysledek == 1)
        {
            printf("\nCislo je provocislem");
        }

        if(vysledek == 2)
        {
            printf("\nCislo NEni provocislem");
        }

//    }

    return 0;
}


///////////////////
//// Primality ////
///////////////////
void primeTester(int64_t *num, int *res)
{

    int64_t cislo;
    int boolean;

    cislo = *num;
    boolean = true;

    for(int i = cislo - 1; i > 1; i--)
    {
        if(cislo % i == 0)    // for example 4 mod3 = 1; 4 mod2 = 0 => there is no reminder
        {
            boolean = false;
        }
    }

    if(boolean)
    {
        *res = 1;
    }
    else
    {
        *res = 2;
    }

}


```
