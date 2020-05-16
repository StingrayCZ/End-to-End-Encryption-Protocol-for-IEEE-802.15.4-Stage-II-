# ECDH

This repository contains invidually components of ECDH algorithm.

## Recogniser

This algorithm is able to make a decision what method will be use.

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int Xi, Yi, Xj, Yj, modulus, a, b, result;

    a = 1;
    b = 6;

    while(1)
    {



        // Zadani prvniho bodu Xi, Yi
        printf("Zadani prvniho bodu\n\r");
        printf("Zadej Xi:");
        scanf("%d", &Xi);
        printf("Zadej Yi:");
        scanf("%d", &Yi);

        printf("\n\r");

        // Zadani druhe bodu Xj, Yj
        printf("Zadani druheho bodu\n\r");
        printf("Zadej Xj:");
        scanf("%d", &Xj);
        printf("Zadej Yj:");
        scanf("%d", &Yj);

        result = Recognizer(&Xi, &Yi, &Xj, &Yj);

        printf("\n\r");
        printf("Vysledek je %d\n\r", result);
        printf("\n\r");
    }

    return 0;
}


int Recognizer(int *Xi, int *Yi, int *Xj, int *Yj)
{
    int xa, ya, xb, yb;

    xa = *Xi;
    ya = *Yi;

    xb = *Xj;
    yb = *Yj;

    if(xa == xb) // Jsou-li body souradnice xa a xb stejne
    {

        if(ya == yb)  // A zaroven sou ya a yb rozdilna, pouzije se fungkce diff, priznak 1
        {
            return 1;
        }
        else
        {
            return 66; // End of program. It shouldn't happens
        }
    }

    else if(xa != xb)
    {

        return 2;   // pouzije se funkce different
    }
}

```

## Return Array

```sh
#include <stdio.h> 
  
int* fun() 
{ 
    int arr[100]; 
  
    /* Some operations on arr[] */
    arr[0] = 10; 
    arr[1] = 20; 
  
    return arr; 
} 
  
int main() 
{ 
    int* ptr = fun(); 
    printf("%d %d", ptr[0], ptr[1]); 
    return 0; 
} 
```
