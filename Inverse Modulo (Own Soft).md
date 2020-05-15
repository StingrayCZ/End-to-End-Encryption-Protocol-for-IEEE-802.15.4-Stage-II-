## Inverse Modulo (prototype)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    while(1)
    {
        SuperEuler();
    }

    return 0;
}


int SuperEuler()
{

    int cislo;
    int delitel;

    printf("\n\rZadej cislo, ktere je c^(-1)\n");
    scanf("%d", &cislo);

    printf("\nZadej cislo, ktere bude delit)\n");
    scanf("%d", &delitel);

    int mod=2;
    int i = 1;

    while(mod >= 2)
    {

        mod = (cislo * i)%delitel;
        i++;
    }

    i = i - 1;


    if(mod == 0){

            printf("Cislo %d neni invertibilni", cislo);

    }
    else{

    //printf("\nModulus je: %d", mod);
    printf("\nInverze je: %d", i);
    printf("\n");

    }


}

```
