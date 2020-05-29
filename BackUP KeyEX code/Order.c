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
                printf("Body jsou [%4d,%4d] [%2d,%2d] \n\r", x, y, x, y_neg);

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
