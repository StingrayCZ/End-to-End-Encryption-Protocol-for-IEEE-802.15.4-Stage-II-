## FIRST POINT algorithm (prototype)

```sh
#include <stdio.h>
#include <stdlib.h>

void YPart();
int power();
int modulo();
void ObtainOrder();
void TheFirstPoint();

int main ()
{
    int modulus;
    // FROM NEXT ALGORTHM
    int a ,b;

    printf ("Napis modulus:\n\r");
    scanf ("%d", &modulus);
    printf ("Napis a:\n\r");
    scanf ("%d", &a);
    printf ("Napis b:\n\r");
    scanf ("%d", &b);

    TheFirstPoint(&modulus, &a, &b);


}

void TheFirstPoint(int *MOD, int *A, int *B)
{
    int modulus, a, b;
    int poleA[1000];
    int poleB[1000];

    modulus = *MOD;
    a = *A;
    b = *B;

    // Application A
    YPart (&modulus, poleA);

    int iter = ((modulus - 1) / 2);

    for(int i = 0; i <= iter; i++)
    {

        printf("Hodnota je %d\n\r", poleA[i]);
    }

    // Application B
    ObtainOrder(&modulus, &a, &b, poleB);
    int x = 0; // The first test is x=0, next ones are soluted by for cycle

    for(int i = 1; i <= modulus; i++)
    {

        printf("Vysledek pro X = %d je %d\n\r", x, poleB[i]);
        x++;
    }

 }

//////////////////////////////////
//// OBTAIN ORDER OF GROUP ///////
//////////////////////////////////
void ObtainOrder(int *P, int *A, int *B, int nums[])
{

    int p, a,b, mocnina, compute, x;

    p = *P;
    a = *A;
    b = *B;
    mocnina = 3; // Weierstrass method

    // Weierstrass equation y^2 = x^3 + ax + b

    x = 0; // The first test is x=0, next ones are soluted by for cycle

    for(int i = 1; i <= p; i++)
    {

        compute = power(&x, &mocnina) + a * x + b;

        nums[i] = modulo(&compute, &p);

        x++;
    }

}


//////////////////////////////////
//// COMP. ARRAY Y and Y^2 ///////
//////////////////////////////////
void YPart(int *modulus, int nums[])
{

    int iter, mod, mocnitel, number;

    // number aux. variable

    iter = *modulus;
    mod = *modulus;

    mocnitel = 2;   // Weierstrass method
    iter = ((iter - 1) / 2);  // Count of iteration


    for(int i = 0; i <= iter; i++)
    {

        number = power(&i, &mocnitel);
        nums[i] = modulo(&number, &mod);

    }

    nums[0] = 0;   // Fixed according the Weierstrass method

}

//////////////////////////////////
//// POWER ///////////////////////
//////////////////////////////////
int power(int *num, int *power)
{

    int numpow = *num;

    for(int i = 1; i < *power; i++)
    {

        numpow *= *num;
    }

    return numpow;
}

//////////////////////////////////
//// MODULO //////////////////////
//////////////////////////////////
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

    return 0;
}


```
