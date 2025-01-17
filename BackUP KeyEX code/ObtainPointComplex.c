#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void ObtainPointComplex(int *mod, int *a_parameter, int *b_parameter, int *X_first, int *Y_first, int *G_Order)
{
// Generator of random numbers
    srand((unsigned int) time(NULL));
    int Throttle = 300;                 // Throttle of power


    // Values for obtain the first point and order
    int modulus;                      // modulus
    int a,b;                          // paramereters a and b

    int TESTparameters, TESTmodulo;   // Test values for primality

    // Obtaining the first point
    int Xfirst, Yfirst, OrderG;

    // The last point verification
    int XLast, YLast, parityVal;

    // Container
    int container[2];

    // STOP Value
    static int stopVal;

    // GENERETION OF GROUP

    do
    {

        do
        {

            // SET of MODULUS
            do
            {
//                modulus = rand() % Throttle;
modulus = 7;

                // Examination of modulus
                TESTmodulo = primeTester(&modulus, &TESTmodulo);

            }
            while(TESTmodulo == 2);
a = 1;
b = 6;
//            a = rand() % Throttle;
//            b = rand() % Throttle;

            // Examination of a and b
            while(TESTparameters == 0)
            {

//                a = rand() % Throttle;
//                b = rand() % Throttle;

                checkValAB(&modulus, &a, &b, &TESTparameters);

            }

            printf("\nModulus je %d", modulus);
            printf("\nParametry jsou %d a %d\n", a, b);


            // Input: modulus, a, b
            // Output: Xfirst, Yfirst, OrderG
            TheFirstPoint(&modulus, &a, &b, &Xfirst, &Yfirst, &OrderG);


            printf("\n\rThe first point is [%d, %d] and order of group is %d", Xfirst, Yfirst, OrderG);
            printf ("\n\r");


            PointComp(&Xfirst, &Yfirst, &a, &modulus, &OrderG, container, &stopVal);

            XLast = container[0];
            YLast = container[1];

            VerifyOfPoint(&modulus, &XLast, &YLast, &a, &b, &parityVal);

            printf("\n Hodnota X posledniho bodu je: %d", XLast);
            printf("\n Hodnota Y posledniho bodu je: %d", YLast);
            printf("\n Hodnota parity je: %d", parityVal);

            printf("\n Hodnota stopVal je: %d", stopVal);

        }
        while(parityVal == 66);

        }
    while(stopVal == 66);


    *mod = modulus;
    *a_parameter = a;
    *b_parameter = b;
    *X_first = Xfirst;
    *Y_first = Yfirst;
    *G_Order = OrderG;

}
