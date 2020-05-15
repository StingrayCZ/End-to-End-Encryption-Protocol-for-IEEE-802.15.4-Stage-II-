## Inverse Modulu (Second generation)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cislo, modulo, vysledek;

    printf("\n\rZadej cislo, ktere je c^(-1)\n");
    scanf("%d", &cislo);

    printf("\nZadej cislo, ktere bude delit\n");
    scanf("%d", &modulo);

    vysledek = InverseMod(&cislo, &modulo);

    printf("Vysledek je %d", vysledek);

}


int InverseMod(int *Num, int *Mod)
{

    int usageNum, multiplier, result;

    usageNum = *Num;
    multiplier = 1;

    if(usageNum > 0)  // Je kladne
    {
        do
        {
            result = (usageNum * multiplier) % *Mod;
            multiplier++;
        }
        while (result >= 2);

        multiplier -= 1; // vyrušení přebytečného inkrementu

        return multiplier;
    }

    else if (usageNum < 0) // Je zaporne
    {
        usageNum *= (-1);  // uprava cisla zpet na kladne

        do
        {
            result = (usageNum * multiplier) % *Mod;
            multiplier++;
        }
        while (result >= 2);

        multiplier -= 1; // vyrušení přebytečného inkrementu

        multiplier = *Mod - multiplier;  // Specialni uprava pro zaporne cislo

        return multiplier;
    }
}
```

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
