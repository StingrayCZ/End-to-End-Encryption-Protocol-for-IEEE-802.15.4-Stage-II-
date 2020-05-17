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

## Computing order of EC (Stage I)

```sh
#include <stdio.h>

int main()
{
    int p = 7;
    
    int modulus = 7;
    
    int number, mocnitel;
    
    mocnitel = 2;
    
    
    int nums[p];
    
    //int c = 4;
    
    //nums[0] = 1988;
    //nums[1] = 1992;
    //nums[2] = 1993;
    //nums[3] = 2004;
    //nums[c] = 2033;
    
    for(int i = 0; i <= 3; i++){
        
        number = power(&i, &mocnitel);
        
        
        nums[i] = modulo(&number, &modulus);
    
    }
    
    for(int i = 0; i <= 3; i++){
        
        printf("%d. poradi => Hodnota je %d\n\r", i, nums[i]);
    
    }

    return 0;
}


/included modules
// int modulo (int *num, int *mod, int tempNum)
// int power(int *num, int *power, int numpow)


```


## BakcUP

```sh
#include <stdio.h>
#include <stdlib.h>

int main ()
{

    int modulus, result;

    printf ("Napis modulus:\n\r");
    scanf ("%d", &modulus);

    result = YPart (&modulus);


    printf("Hodnota je %d\n\r", result[2]);

    return 0;
}


int YPart(int *modulus)
{

    int MOD, MODu, mod, mocnitel, number;

    // number je mezivypocet`

    MOD = *modulus;
    mod = *modulus;

    mocnitel = 2;   // Weierstrass method
    MOD = ((MOD - 1) / 2);  // Iteraci
    MODu = 4; // Upraveny pocet iteraci pro pole

    printf("Hodnota MOD je %d\n", MOD);
    printf("Hodnota MODu je %d\n", MODu);


    int nums[MODu]; // deklarace pole


    for(int i = 0; i <= (MOD); i++)
    {

            number = power(&i, &mocnitel);
            nums[i] = modulo(&number, &mod);

    }

    nums[0] = 0;   // Oprava dle Weierstrass method

    for(int i = 0; i <= (MOD); i++)
    {

        printf("Hodnota je %d\n\r", nums[i]);
    }

    return nums;
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


int modulo (int *num, int *mod, int tempNum)
{


    tempNum = *num;

    if(tempNum > 0) // Je kladne
    {
        tempNum %= *mod;    // Vypocet modula

        return tempNum;     // Navrat vypocitane hodnoty cyklu
    }

    else if(tempNum < 0)  // Je zaporne
    {
        tempNum *= (-1);  // uprava cisla zpet na kladne

        tempNum %= *mod;  // Vypocet modula

        tempNum = *mod - tempNum;  // Specialni uprava pro zaporne cislo

        return tempNum;    // Navrat vypocitane hodnoty cyklu
    }

}


```
