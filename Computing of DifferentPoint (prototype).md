## Computing of DifferentPoint (prototype) - Work In Progress

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Test Mode
    int Xi, Yi, Xj, Yj, a, MOD, Lambda, X_k, Y_k;

    Xi = 1;
    Yi = 1;

    Xj = 2;
    Yj = 3;

    a = 1;
    MOD = 7;


    Lambda = LamdaDiff(&MOD, &Xi, &Yi, &Xj, &Yj, &a);

//    X_k = XSame(&MOD, &Lambda, &X);
//
//    Y_k = YSame(&MOD, &Lambda, &X, &Y, &X_k);


    printf("Lamba je %d\n\r", Lambda);
//    printf("Bod X je %d\n\r", X_k);
//    printf("Bod Y je %d\n\r", Y_k);


    return 0;
}

int XSame(int *MOD, int *Lambda, int *X){

    int modulus, lambda, x, mocnitel;

    modulus = *MOD;
    lambda = *Lambda;
    x = *X;
    mocnitel = 2;   // According to Weierstrass equation

    lambda = power(&lambda, &mocnitel);


    lambda -= (2 * x);

    x = modulo(&lambda, &modulus);

    return x;
}


//int YSame(int *MOD, int *Lambda, int *X, int *Y, int *X_k){
//
//    int modulus, lambda, x, y, x_k;
//
//    modulus = *MOD;
//    lambda = *Lambda;
//    x = *X;
//    y = *Y;
//    x_k = *X_k;
//
//    y = lambda * (x - x_k) - y;
//
//    y = modulo(&y, &modulus);
//
//    return y;
//
//}



int LamdaDiff(int *MOD, int*Xi, int *Yi, int*Xj, int *Yj, int *a)
{

    int cisloXi, cisloYi, cisloXj, cisloYj, modulus, mocnitel, a_value; // inner data containers
    int HighLine, LowLine, FinalLine;     // auxilary

    cisloXi = *Xi;
    cisloYi = *Yi;
    cisloXj = *Xj;
    cisloYj = *Yj;
    modulus = *MOD;
    mocnitel = 2;    // According to Weierstrass equation
    a_value = *a;



    HighLine = cisloYj - cisloYi;
    LowLine = cisloXj - cisloXi;

    HighLine = modulo(&HighLine, &modulus);
    LowLine = InverseMod(&LowLine, &modulus);

    FinalLine = HighLine * LowLine;
    FinalLine = modulo(&FinalLine, &modulus);


    return FinalLine;

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


int power(int *num, int *power, int numpow)
{

    numpow = *num;

    for(int i = 1; i < *power; i++)
    {

        numpow *= *num;
    }

    return numpow;
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
