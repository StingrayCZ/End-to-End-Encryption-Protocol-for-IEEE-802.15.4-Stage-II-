## Výměna klíčů

### Main.c

Testovní vstupů. Vstupy *scanf* jsou pouze pro účely testování, budou nahrazeny funkci pro generování pseudonáhodných čísel.

```sh
#include <stdio.h>
#include <stdlib.h>

#include "function.h"


int main ()
{
    int modulus;
    // FROM NEXT ALGORTHM
    int a,b;
    int TESTparameters, TESTmodulo;

    // Obtaining the first point
    int Xfirst, Yfirst, OrderG;

    // Container
    int container[2];

    //Primality test

    // SET of MODULUS
    do{
        printf ("Napis modulus:\n\r");
        scanf ("%d", &modulus);

        // Examination of modulus
        TESTmodulo = primeTester(&modulus, &TESTmodulo);

        if(TESTmodulo == 2)
        {
            printf ("Zadane modulo neni prvo cislo, zadej znovu\n\r");
            printf ("\n\r");
        }
    }while(TESTmodulo == 2);


    // SET of PARAMETERS
    printf ("Napis a:\n\r");
    scanf ("%d", &a);
    printf ("Napis b:\n\r");
    scanf ("%d", &b);

    // Examination of a and b
    while(TESTparameters == 0)
    {
        printf ("Napis a:\n\r");
        scanf ("%d", &a);
        printf ("Napis b:\n\r");
        scanf ("%d", &b);

        checkValAB(&modulus, &a, &b, &TESTparameters);

        if(TESTmodulo == 0)
        {
            printf ("Zadani parametru nevyhovuje, zadej znovu\n\r");
            printf ("\n\r");
        }
    }


    // Input: modulus, a, b
    // Output: Xfirst, Yfirst, OrderG
    TheFirstPoint(&modulus, &a, &b, &Xfirst, &Yfirst, &OrderG);


    printf("\n\rThe first point is [%d, %d] and order of group is %d", Xfirst, Yfirst, OrderG);
    printf ("\n\r");


    PointComp(&Xfirst, &Yfirst, &a, &modulus, &OrderG, container);

}
```

### MAT.c (Matematické funkce)

V zimním semestru jsem měl problém s mocněním, které vrací desetinné číslo na vstupu. Další problém je, pokud nastane situace 5^2. To výpočet vrtátí nesprávnou hodnotu 24. Je zde také potřeba výpočtu záporných hodnot pomocí modulo funkce. Obdobný problém byl i výpočtu inverzní funkce modulo. Všechny tyto problémy jsou vyřešeny pomocí následujících funkcí, které jsou dle potřebu v průběhu činnosti volány. Čvtou funkcí v této části kódu je testovací algoritmus, který má za úkol prověřovat pseudonáhodná čísla ze vstupu, zda jsou to pročísla.

```sh
#include <stdio.h>
#include "function.h"
#include <stdbool.h>

///////////////////
//// Primality ////
///////////////////
int primeTester(int *num, int *result)
{

    static int cislo, boolean;

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
        return 1;
    }
    else
    {
        return 2;
    }

    return 0;
}



//////////////////////////////////
//// MODULO //////////////////////
//////////////////////////////////f
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

    return 0;
}

```
## Order.c (Výpočet prvního bodu a řádu grupy bodů)

Účelem tohoto algoritmu je výpočet prvnáho bodu a řádu grupy z hodnoty p (modulus), a a b (parametry). Výsledné hodnoty se použijí pro otestování grupye, jestli je paritní, resp. jestli je použitelná pro výměnu klíčů. Hodnota řádu je mimo jiné důležitá i pro výpočet tajného bodu, kde náhodně vygenerovaný klíč musí být "zarovnán" do itervalu od 1 do hodnoty řády grupy.

```sh
#include <stdio.h>
#include "function.h"

/////////////////////////////////////////
//// Condition of parameters a and b ////
////////////////////////////////////////
void checkValAB(int *mod, int *A, int *B, int *TESTvalue)
{
    int a, b, compute, mocnitelA, mocnitelB, MOD;

    MOD = *mod;
    a = *A;
    b = *B;

    if(a == MOD)
    {

        *TESTvalue = 0;
    }

    else if(b == MOD)
    {

        *TESTvalue = 0;
    }

    else
    {
        mocnitelA = 3;
        mocnitelB = 2;

        compute =  4 * (power(&a, &mocnitelA)) + 27 * (power(&b, &mocnitelB));
        compute = modulo(&a, &MOD);

        *TESTvalue = compute;

    }
}

//////////////////////////////////////////////////////
//// Finder of the first point and order of group ///
/////////////////////////////////////////////////////
void TheFirstPoint(int *MOD, int *A, int *B, int*Xfirst, int*Yfirst, int *OrderG)
{
    int modulus, a, b;
    int poleA[1000];
    int poleB[1000];

    modulus = *MOD;
    a = *A;
    b = *B;

    // Computing order
    int order = 0;

    // Application A
    YPart (&modulus, poleA);

    // Iterations
    int X_iter = modulus - 1;
    int Y_iter = ((modulus - 1) / 2) + 1;

    // Points
    static int x, y, y_neg;

    // Application B
    XPart(&modulus, &a, &b, poleB);

    for(int k = 0; k <= X_iter; k++)  // Give X's
    {
        for(int i = 0; i <= Y_iter; i++)  // Give Y's
        {
            if (poleA[i] == poleB[k])
            {
                if(order == 0)
                {

                    *Xfirst = k;
                    *Yfirst = i;
                }

                x = k;
                y = i;
                y_neg = modulus - i;

                //printf("Yes, this number is in array\n\r");
                // printf("Jedna se o cisla %d a %d\n\r", poleA[i], poleB[k]);
                // printf("\n\r");
                printf("Body jsou [%d,%d] [%d,%d] \n\r", x, y, x, y_neg);

                order++;

            }
        }

    }

    order *= 2;
    order += 1;

    *OrderG = order;
}

//////////////////////////////////
//// COMP. ARRAY X ///////////////
//////////////////////////////////
void XPart(int *P, int *A, int *B, int nums[])
{

    int p, a,b, mocnina, compute, x;

    p = *P;
    a = *A;
    b = *B;
    mocnina = 3; // Weierstrass method

    // Weierstrass equation y^2 = x^3 + ax + b

    x = 0; // The first test is x=0, next ones are soluted by for cycle

    for(int i = 0; i <= p; i++)
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


    for(int i = 1; i <= iter; i++)
    {

        number = power(&i, &mocnitel);
        nums[i] = modulo(&number, &mod);

    }

    nums[0] = 0;   // Fixed according the Weierstrass method

}
```

### Provider.c (Vypocet ostatních bodů)
Tato aplikace je schopna ze znalosti prvního bodu, parametru, řádu grupy a počtu itarací spočítat jakýkoliv bod, který je obsažen v grupě. Pokud se počet iterací rovná hodnotě řádu grupy, jsou vypočítány všechny body a je tak ověřena funkčnost vygenerované grupy. Iterace mají i účel pro výpočet bodů z grupy na základě klíče.

```sh
#include <stdio.h>
#include "function.h"


//////////////////////////////////
//// PROVIDER OF POINT ///////////
//////////////////////////////////

void PointComp(int *X, int *Y, int *a_asymptote, int *modulus, int *iteration, int pole[])
{
    int Xi, Yi, Xj, Yj;
    int MOD, a;

    static int Lambda, X_k, Y_k;   //pouze v ramci teto funkce
    int result;                    //declaration of result
    int iter;

    // Input of value
    Xi = *X;
    Yi = *Y;


    // Copy first point to second, as 1P + 1P = 2P
    Xj = Xi;
    Yj = Yi;

    a = *a_asymptote;
    MOD = *modulus;

    // Value for number of iteration
    iter = *iteration;


    for(int i = 1; i <= iter - 2; i++)
    {
        result = Recognizer(&Xi, &Yi, &Xj, &Yj); // Navrat hodnoty, ktera rozhodne, ktera metoda se pouzije

        if(result == 1)
        {
            Lambda = LamdaSame(&MOD, &Xi, &Yi, &a);
            X_k = XSame(&MOD, &Lambda, &Xi);
            Y_k = YSame(&MOD, &Lambda, &Xi, &Yi, &X_k);

                EMPTYLINE
                printf("Bod: [%d, %d]\n\r", X_k, Y_k);


        }

        else if(result == 2)
        {
            Lambda = LamdaDiff(&MOD, &Xi, &Yi, &Xj, &Yj);
            X_k = XDiff(&MOD, &Lambda, &Xi, &Xj);
            Y_k = YDiff(&MOD, &Lambda, &Xi, &Yi, &X_k);

                EMPTYLINE
                printf("Bod: [%d, %d]\n\r", X_k, Y_k);

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


    pole[0] = X_k;
    pole[1] = Y_k;

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
            return 1;
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

### Functions.h (knihovna)

V této části je knihovna, která obsahuje linkery na jednotlivé bloky kódu.

```sh

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void PointComp();
int LamdaSame();
int LamdaDiff();
int XSame();
int XDiff();
int YSame();
int YDiff();
int Recognizer();

int modulo();
int power();
int InverseMod();
int primeTester();

void YPart();
void XPart();
void TheFirstPoint();
void checkValAB();
#endif // FUNCTIONS_H






#ifndef AUX_FUNCT
#define AUX_FUNCT

#define EMPTYLINE printf("\n\r");

#endif // AUX_FUNCT


```
