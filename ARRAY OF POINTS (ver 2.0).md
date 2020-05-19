##  Array of Poiunts (version 2)

Tato verze je resena jako samostatny blok, kteryy je inicializovan z radku.

```sh
int main()
{


    int  Xi, Yi, MOD, a, b;
    int poradi;

    Xi = 13;
    Yi = 7;
    a = 2;
    b = 2;
    MOD = 17;

    poradi = 17;


    PointComp(&Xi, &Yi, &a, &b, &MOD, &poradi);

}
```

```sh
#include <stdio.h>
#include <stdlib.h>


int PointComp(int *X, int *Y, int *a_asymptote, int *b_asymptote, int *modulus, int *iteration)
{
    int Xi, Yi, Xj, Yj;
    int MOD, a, b;
    int Lambda, X_k, Y_k;
    int result;  //declaration of result
    int iter;

    // Input of value
    Xi = *X;
    Yi = *Y;


    // Copy first point to second, as 1P + 1P = 2P
    Xj = Xi;
    Yj = Yi;

    a = *a_asymptote;
    b = *b_asymptote;
    MOD = *modulus;

    // Value for number of iteration
    iter = *iteration;


    for(int i = 1; i <= iter; i++)
    {
         result = Recognizer(&Xi, &Yi, &Xj, &Yj); // Navrat hodnoty, ktera rozhodne, ktera metoda se pouzije

            if(result == 1)
            {
                Lambda = LamdaSame(&MOD, &Xi, &Yi, &a);
                X_k = XSame(&MOD, &Lambda, &Xi);
                Y_k = YSame(&MOD, &Lambda, &Xi, &Yi, &X_k);

                printf("\n\r");
                printf("Hodnota X = %d\n\r", X_k);
                printf("Hodnota X = %d\n\r", Y_k);

            }

            else if(result == 2)
            {
                Lambda = LamdaDiff(&MOD, &Xi, &Yi, &Xj, &Yj, &a);
                X_k = XDiff(&MOD, &Lambda, &Xi, &Xj);
                Y_k = YDiff(&MOD, &Lambda, &Xi, &Yi, &X_k);

                printf("\n\r");
                printf("Hodnota X = %d\n\r", X_k);
                printf("Hodnota X = %d\n\r", Y_k);

            }

            else if(result == 66)
            {
                printf("Nereseitelne");
            }


            Xj = X_k;
            Yj = Y_k;

    }

//    printf("Hodnota X = %d\n\r", X_k);
//    printf("Hodnota Y = %d\n\r", Y_k);

    return 0;
}

//////////////////////////////////
//// LAMBDA SAME /////////////////
//////////////////////////////////
int LamdaSame(int *MOD, int*X, int *Y, int *a)
{

    int cisloX, cisloY, modulus, mocnitel, a_value; // inner data containers
    int HighLine, LowLine, FinalLine;     // auxilary

    cisloX = *X;
    cisloY = *Y;
    modulus = *MOD;
    mocnitel = 2;    // According to Weierstrass equation
    a_value = *a;



    HighLine = 3 * (power(&cisloX, &mocnitel)) + a_value;
    LowLine = 2 * cisloY;

    HighLine = modulo(&HighLine, &modulus);
    LowLine = InverseMod(&LowLine, &modulus);

    FinalLine = HighLine * LowLine;
    FinalLine = modulo(&FinalLine, &modulus);


    return FinalLine;
}

//////////////////////////////////
//// LAMBDA DIFFERENT ////////////
//////////////////////////////////
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


//////////////////////////////////
//// X POINT SAME ////////////////
//////////////////////////////////
int XSame(int *MOD, int *Lambda, int *X)
{

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

//////////////////////////////////
//// X POINT DIFFERENT ///////////
//////////////////////////////////
int XDiff(int *MOD, int *Lambda, int *Xi, int *Xj)
{

    int modulus, lambda, cisloXi, cisloXj, mocnitel, x_result;

    modulus = *MOD;
    lambda = *Lambda;
    cisloXi = *Xi;
    cisloXj = *Xj;
    mocnitel = 2;   // According to Weierstrass equation

    lambda = power(&lambda, &mocnitel);


    lambda = lambda - cisloXi - cisloXj;

    x_result = modulo(&lambda, &modulus);

    return x_result;
}

//////////////////////////////////
//// Y POINT SAME ////////////////
//////////////////////////////////
int YSame(int *MOD, int *Lambda, int *X, int *Y, int *X_k)
{

    int modulus, lambda, x, y, x_k;

    modulus = *MOD;
    lambda = *Lambda;
    x = *X;
    y = *Y;
    x_k = *X_k;

    y = lambda * (x - x_k) - y;

    y = modulo(&y, &modulus);

    return y;
}

//////////////////////////////////
//// Y POINT DIFFERENT  //////////
//////////////////////////////////

int YDiff(int *MOD, int *Lambda, int *X, int *Y, int *X_k)
{

    int modulus, lambda, x, y, x_k;

    modulus = *MOD;
    lambda = *Lambda;
    x = *X;
    y = *Y;
    x_k = *X_k;

    y = lambda * (x - x_k) - y;

    y = modulo(&y, &modulus);

    return y;

}


//////////////////////////////////
//// DECISION ALGORITHM //////////
//////////////////////////////////
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

}

//////////////////////////////////
//// POWER ///////////////////////
//////////////////////////////////
int power(int *num, int *power, int numpow)
{

    numpow = *num;

    for(int i = 1; i < *power; i++)
    {

        numpow *= *num;
    }

    return numpow;
}


//////////////////////////////////
//// INVERSE MODULO //////////////
//////////////////////////////////
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

        multiplier -= 1; // vyrušení pøebyteèného inkrementu

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

        multiplier -= 1; // vyrušení pøebyteèného inkrementu

        multiplier = *Mod - multiplier;  // Specialni uprava pro zaporne cislo

        return multiplier;
    }
}

```
