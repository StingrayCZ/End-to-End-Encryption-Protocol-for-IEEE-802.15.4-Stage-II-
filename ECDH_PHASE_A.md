## ECDH_PHASE_I

```c
void ECDH_PHASE_A(int *mod, int *a_parameter, int *b_parameter, int *X_first, int *Y_first, int *G_Order)
{
	// Generator of random numbers
	srand((unsigned int) time(NULL));
	int Throttle = 30;                 // Throttle of power


	// Values for obtain the first point and order
	int modulus;                      // modulus
	int a,b;                          // paramereters a and b

	int TESTparameters, TESTmodulo;   // Test values for primality

	// Obtaining the first point
	int Xfirst, Yfirst, OrderG;

	// The last point verification
	int XLast, YLast, parityVal;

	// Container (First X, First Y, Order)
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
				modulus = rand() % Throttle;
				
				// Examination of modulus
				TESTmodulo = primeTester(&modulus, &TESTmodulo);

			}
			while(TESTmodulo == 2);

			            a = rand() % Throttle;
			            b = rand() % Throttle;

			// Examination of a and b
			while(TESTparameters == 0)
			{

				                a = rand() % Throttle;
				                b = rand() % Throttle;

				checkValAB(&modulus, &a, &b, &TESTparameters);

			}
			
			#ifdef PRINT_ON
			printf("\nModulus je %d", modulus);
			printf("\nParametry jsou %d a %d\n", a, b);
			#endif // PRINT_ON


			// Input: modulus, a, b
			// Output: Xfirst, Yfirst, OrderG
			TheFirstPoint(&modulus, &a, &b, &Xfirst, &Yfirst, &OrderG);
			
			#ifdef PRINT_ON
			printf("\n\rThe first point is [%d, %d] and order of group is %d", Xfirst, Yfirst, OrderG);
			printf ("\n\r");
			#endif // PRINT_ON


			PointComp(&Xfirst, &Yfirst, &a, &modulus, &OrderG, container, &stopVal);

			XLast = container[0];
			YLast = container[1];

			VerifyOfPoint(&modulus, &XLast, &YLast, &a, &b, &parityVal);
			
			#ifdef PRINT_ON
			printf("\n Value of X the last point is: %d", XLast);
			printf("\n Value of Y the last point is: %d", YLast);
			printf("\n Value of parity is: %d", parityVal);
			printf("\n Value of stopVal is: %d", stopVal);
			#endif // PRINT_ON

		}
		while(parityVal == 66);

	}
	while(stopVal == 66);
	
	// -- Output of results --
	*mod = modulus;
	*a_parameter = a;
	*b_parameter = b;
	*X_first = Xfirst;
	*Y_first = Yfirst;
	*G_Order = OrderG;

}
```
