## STACK componets

### Security enable
```sh
#if defined(NWK_ENABLE_SECURITY) && (SYS_SECURITY_MODE == 0)
  #define PHY_ENABLE_AES_MODULE
#endif

#endif // _SYS_CONFIG_H_
```

### Testing ECDH modules (printing random number)

```sh
#ifdef USB_DEBUG
TESTRAND = rand();
printf("\r\nRandom cislo je %d",TESTRAND);
#endif
```

### Testing ECDH modules (printing random number)
Změna **int** na **modulo**.

```sh
int cislo, modularo, result;
```
```sh
#ifdef USB_DEBUG
printf("\r\nZadej cislo: ");

scanf("%d", &cislo);


printf("\r\nZadej modulus: ");

scanf("%d", &modularo);

result = modulo (&cislo, &modularo);


printf("\r\nVysledek je %d", result);
#endif
```
### Stack TEST

```sh
#ifdef USB_DEBUG

// GENERETION OF GROUP

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

	printf("\r\nModulus je %d", modulus);
	printf("\r\nParametry jsou %d a %d\n", a, b);


	// Input: modulus, a, b
	// Output: Xfirst, Yfirst, OrderG
	TheFirstPoint(&modulus, &a, &b, &Xfirst, &Yfirst, &OrderG);


	printf("\n\rThe first point is [%d, %d] and order of group is %d", Xfirst, Yfirst, OrderG);
	printf ("\n\r");


	PointComp(&Xfirst, &Yfirst, &a, &modulus, &OrderG, container, &stopVal);

	printf("\r\n Hodnota stopVal je: %d", stopVal);

}while(stopVal > 2);


#endif

```
