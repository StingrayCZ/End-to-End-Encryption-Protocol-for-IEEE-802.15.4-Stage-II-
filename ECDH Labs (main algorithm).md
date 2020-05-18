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

## Return Array (bad example)

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

## Computing order of EC (Stage I - prototype)

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


## Computing order of EC (Stage I - Final)

```sh
#include <stdio.h>
#include <stdlib.h>

int main ()
{

    int modulus, result;

    printf ("Napis modulus:\n\r");
    scanf ("%d", &modulus);

    result = YPart (&modulus);


    //printf("Hodnota je %d\n\r", result[2]);

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

//    int nums[] = {0}; // Incializace pole

    int nums[MODu];  // Incializace pole

    for(int i = 0; i <= MOD; i++)
    {

        number = power(&i, &mocnitel);
        nums[i] = modulo(&number, &mod);

    }

    nums[0] = 0;   // Oprava dle Weierstrass method

    for(int i = 0; i <= MOD; i++)
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

## Computing of order EC (Satage II - final)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p, a,b, result;

//    printf("Zadej p (modulus)\n\r");
//    scanf("%d", &p);
//
//    printf("Zadej a\n\r");
//    scanf("%d", &a);
//
//    printf("Zadej b\n\r");
//    scanf("%d", &b);

    p = 17;
    a = 2;
    b = 2;

    result = ObtainOrder(&p, &a, &b);

    printf("Hodnota je: %d", result);


    return 0;
}


ObtainOrder(int *P, int *A, int *B)
{

    int p, a,b, mocnina, compute, x, result;

    p = *P;
    a = *A;
    b = *B;
    mocnina = 3; // Weierstrass method

    // Weierstrass equation y^2 = x^3 + ax + b

    x = 0; // testovaci



    for(int i = 1; i <= 17; i++)
    {

        compute = power(&x, &mocnina) + a * x + b;

        result = modulo(&compute, &p);
        printf("Vysledek pro x = %d je %d\n\r", x, result);

        x++;
    }

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

## Computingnof order EC (Stage III - comparsion of arrays) - prototyp

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

//    int key;

    int arrayA[] = {89, 12, 57, 44, 55, 22, 33, 54, 66, 99, 2, 44};

    int arrayB[] = {12, 66, 2};


//    printf("Napis %d", array[2]);

//    while(1)
//    {
//        printf("Co chces hledat?\n\r");
//        scanf("%d", &key);


        for(int k = 0; k <= 2; k++)
        {

            for(int i = 0; i <= 11; i++)
            {
                if (arrayA[i] == arrayB[k])
                {

                    printf("Yes, this number is in array\n\r");
                    printf("Jedna se o cisla %d a %d\n\r", arrayA[i], arrayB[k]);
                    printf("\n\r");

                }

                else{
                    printf("Neni v rade\n\r");
                }

            }
        }
//
//    }



    return 0;
}

```

## Computingnof order EC (Stage III - comparsion of arrays) - advanced prototyp

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

//    int key;

    int order = 0;

    int arrayA[] = {2, 5, 14, 1, 6, 1, 9, 2, 3, 1, 2, 12, 3, 15, 3, 7, 16};

    int arrayB[] = {0, 4, 9, 16, 8, 2, 15, 13};


//    printf("Napis %d", array[2]);

//    while(1)
//    {
//        printf("Co chces hledat?\n\r");
//        scanf("%d", &key);


    for(int k = 0; k <= 8; k++)
    {

        for(int i = 0; i <= 16; i++)
        {
            if (arrayA[i] == arrayB[k])
            {

                printf("Yes, this number is in array\n\r");
                printf("Jedna se o cisla %d a %d\n\r", arrayA[i], arrayB[k]);
                printf("\n\r");

                order++;

            }

//                else{
//                    printf("Neni v rade\n\r");
//                }

        }
    }
//
//    }

    order *= 2;
    order += 1;


    printf("Rad grupy je %d", order);

           return 0;
}

```

## Array migration

```sh
#include <stdio.h>

int* fun(int *iterace, int *arr)
{
    int iter = *iterace;
    int number = 1;

    for(int i = 1; i <= iter; i++)
    {
        arr[i] = number * 2;
        number++;
    }

    /* Some operations on arr[] */
//    arr[0] = 00;
//    arr[1] = 10;
//    arr[2] = 20;
//    arr[3] = 30;
//    arr[4] = 40;


    return arr;
}

int main()
{
    int iteration = 5;

    int pole[iteration];
    int* ptr = fun(&iteration, pole);

    for(int i = 1; i <= iteration; i++)
    {
        printf("%d\n\r", ptr[i]);
    }

    return 0;
}

```
