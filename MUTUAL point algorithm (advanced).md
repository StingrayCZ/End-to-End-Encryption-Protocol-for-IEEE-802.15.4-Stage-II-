##  Advanced Mutual Point algorithm

```c
#include <stdio.h>
#include <stdlib.h>


void RecognizerSecKey();
void Mutual_Key_Point();

int main()
{
    static int Xf, Yf;         // coordinates of the first point
    static int Xob, Yob;     // coordinates of the obtain point
    static int modulus, a_par;

    static int MySecKey;
    static int ObtainSecKey;
    static int MutualKey;

    static int OrderG;

    MySecKey = 3;

    Xf = 6;
    Yf = 5;

    Xob = 4;
    Yob = 2;

    modulus = 7;
    a_par = 1;
    OrderG = 11;

    RecognizerSecKey(&Xf, &Yf, &Xob, &Yob, &modulus, &a_par, &ObtainSecKey);

    printf("\nTajny klic z bodu b je %d", ObtainSecKey);


    Mutual_Key_Point(&MySecKey, &ObtainSecKey, &OrderG, &MutualKey);


    printf("\nSpolecny klic je %d", MutualKey);


}


void Mutual_Key_Point(int *SecKA, int *SecKB, int *OrderG, int *mutualKey){

    static int SecKeyM, SecKeyO, OrdG;

    SecKeyM = *SecKA;
    SecKeyO = *SecKB;
    OrdG = *OrderG;

    SecKeyM *= SecKeyO;
    SecKeyM = modulo(&SecKeyM, &OrdG);

    *mutualKey = SecKeyM;

}


void RecognizerSecKey(int *XF, int *YF, int *XO, int *YO, int *modulus, int *a_par, int *cargo)
{
    static int Xo, Yo;
    static int Xi, Yi, Xj, Yj;

    int mod, a;
    int counter, StopVal;
    counter = 1;
    int pole[1];

    // Coordinates of the obtain point from other side
    Xo = *XO;
    Yo = *YO;

    // Coordinates of the fitst point
    Xi = *XF;
    Yi = *YF;

    Xj = Xi;
    Yj = Yi;

    mod = *modulus;
    a = *a_par;


    ///////////////////////

    while(StopVal != 2)
    {

        MutualPoint(&Xi, &Yi, &Xj, &Yj, &mod, &a, pole);

        Xj = pole[0];
        Yj = pole[1];

        counter ++;

        if (pole[0] == Xo  && pole[1] == Yo)
        {
            StopVal = 2;
        }
    }

    *cargo = counter;


    printf("\nBod je [%d, %d]", pole[0], pole[1]);
    printf("\nPoradi je %d", counter);

}



void MutualPoint(int *Xa, int *Ya, int *Xb, int *Yb, int *modulus, int *a_pam, int array[])
{

    int mod, a, Xi, Yi, Xj, Yj;
    static int Lambda;
    int Xk, Yk;

    mod = *modulus;
    a = *a_pam;

    Xi = *Xa;
    Yi = *Ya;

    Xj = *Xb;
    Yj = *Yb;


    int resultD = Recognizer(&Xi, &Yi, &Xj, &Yj);

    if(resultD == 1)
    {

        Lambda = LamdaSame(&mod, &Xi, &Yi, &a);
        Xk = XSame(&mod, &Lambda, &Xi);
        Yk = YSame(&mod, &Lambda, &Xi, &Yi, &Xk);

    }

    else if(resultD == 2)
    {

        Lambda = LamdaDiff(&mod, &Xi, &Yi, &Xj, &Yj);

        Xk = XDiff(&mod, &Lambda, &Xi, &Xj);
        Yk = YDiff(&mod, &Lambda, &Xi, &Yi, &Xk);
    }

    // return values
    array[0] = Xk;
    array[1] = Yk;

}



//////////////////////////////////
//// MODULO //////////////////////
//////////////////////////////////f
int modulo (int *num, int *mod)
{

    long tempNum = *num;

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

        multiplier -= 1; // vyrušení p?ebyte?ného inkrementu

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

        multiplier -= 1; // vyrušení p?ebyte?ného inkrementu

        multiplier = *Mod - multiplier;  // Specialni uprava pro zaporne cislo

        return multiplier;
    }

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

//	printf("\nLamda SAME je %d", FinalLine);

    return FinalLine;
}

//////////////////////////////////
//// LAMBDA DIFFERENT ////////////
//////////////////////////////////
int LamdaDiff(int *MOD, int*Xi, int *Yi, int*Xj, int *Yj)
{

    int cisloXi, cisloYi, cisloXj, cisloYj, modulus; // inner data containers
    int HighLine, LowLine, FinalLine;                // auxilary

    cisloXi = *Xi;
    cisloYi = *Yi;
    cisloXj = *Xj;
    cisloYj = *Yj;
    modulus = *MOD;


    HighLine = cisloYj - cisloYi;
    LowLine = cisloXj - cisloXi;

    HighLine = modulo(&HighLine, &modulus);
    LowLine = InverseMod(&LowLine, &modulus);

    FinalLine = HighLine * LowLine;
    FinalLine = modulo(&FinalLine, &modulus);

//	printf("\nLamda DIFF je %d", FinalLine);

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

        if(ya == yb)  // A zaroven sou ya a yb rozdilna, pouzije se funkce SAME, priznak 1
        {
            if(ya == 0)
            {
                return 66;
            }

            else if(yb == 0)
            {
                return 66;
            }

            else
            {
                return 1;
            }

        }
        else
        {
            return 66; // End of program. It shouldn't happens
        }
    }

    else if(xa != xb)
    {

        return 2;   // pouzije se funkce DIFF
    }

    return 0;
}

```
