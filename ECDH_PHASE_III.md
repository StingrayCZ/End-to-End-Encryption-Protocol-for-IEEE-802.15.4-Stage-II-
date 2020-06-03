## ECDH PHASE III

```c
    
    static int SecKey;
    static int XFirst, YFirst; // coordinates of the first point (My node)
    static int mod, a, orderG;

    static int XO, YO;         // coordinates of the obtain point (opposite node)

    static MutKEY; // result

    static int container[2]; // Mutual Point

    SecKey = 6;
    XFirst = 1,
    YFirst = 1;

    XO = 6;
    YO = 5;

    mod = 7;
    a = 1;
    orderG = 11;

    // Input:  SecKey, XFirst, YFirst, XO, YO, mod, a
    // Output: MutKEY, container(array)
    ECDH_PHASE_C(&SecKey, &XFirst, &YFirst, &XO, &YO, &mod, &a, &orderG, &MutKEY, container);


    printf("\nMutual key is %d", MutKEY);
    printf("\nMutual point is [%d, %d]",container[0], container[1]);
   
```

```c
void ECDH_PHASE_C(int *MSKey, int *XF, int *YF, int *XO, int *YO, int *mod, int *a, int *order, int *MutKEY, int MPoint[]){

	static int Xf, Yf;         // coordinates of the first point
	static int Xob, Yob;       // coordinates of the obtain point
	static int modulus, a_par;

	static int MySecKey;
	static int ObtainSecKey;
	static int MutualKey;

	static int OrderG;

	static int container[2]; // Mutual Point
	static int iterator; // number of iteration
	static voidValue;    // excess value


	MySecKey = *MSKey;

	Xf = *XF;
	Yf = *YF;

	Xob = *XO;
	Yob = *YO;

	modulus = *mod;
	a_par = *a;
	OrderG = *order;

	RecognizerSecKey(&Xf, &Yf, &Xob, &Yob, &modulus, &a_par, &ObtainSecKey);

	#ifdef PRINT_ON
	printf("\nRecongnized secret key from other side is %d", ObtainSecKey);
	#endif // PRINT_ON

	Mutual_Key_Point(&MySecKey, &ObtainSecKey, &OrderG, &MutualKey);

	#ifdef PRINT_ON
	printf("\nMutual key is %d", MutualKey);
	#endif // PRINT_ON



	iterator = MutualKey;
	iterator += 1;

	// Compute mutual point
	PointComp(&Xf, &Yf, &a_par, &modulus, &iterator, container, &voidValue);


	// return result
	*MutKEY = MutualKey;

	MPoint[0] = container[0];
	MPoint[1] = container[1];

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

		SumTwoPoints(&Xi, &Yi, &Xj, &Yj, &mod, &a, pole);

		Xj = pole[0];
		Yj = pole[1];

		counter ++;

		if (pole[0] == Xo  && pole[1] == Yo)
		{
			StopVal = 2;
		}
	}

	*cargo = counter;

	#ifdef PRINT_ON
	printf("\nBod je [%d, %d]", pole[0], pole[1]);
	printf("\nPoradi je %d", counter);
	#endif // PRINT_ON


}

```
