## LambdaDiff

```C
#include <stdio.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

int LamdaDiffBIGD(BB RESULT, BB MOD, BB Xi, BB Yi, BB Xj, BB Yj)
{

	BB modulus, XA, YA, XB, YB; // inner data containers
	BB ComparePattern;
	BB resultA, resultB, resultC, FIN;    // auxiliary
	
	uint8_t Compare;
	
	assert(RESULT && MOD && Xi && Yi && Xj && Yj);
	
	/* Use temp */
	modulus = bdNew();
	XA = bdNew();
	YA = bdNew();
	XB = bdNew();
	YB = bdNew();
	
	resultA = bdNew();
	resultB = bdNew();
	resultC = bdNew();
	FIN = bdNew();
	
	bdSetEqual(modulus, MOD);
	bdSetEqual(XA, Xi); 
	bdSetEqual(YA, Yi); 
	bdSetEqual(XB, Xj); 
	bdSetEqual(YB, Yj);
	
	
	bdModSub(resultA, YB, YA, modulus);
	
	bdSubtract(resultB, XB, XA);
	
	bdModInv(resultC, resultB, modulus);
	
	bdModMult(FIN, resultA, resultC, modulus);
	
		
	bdSetEqual(RESULT, FIN);
	
	
	bdFree(&modulus);
	bdFree(&XA);
	bdFree(&YA);
	bdFree(&XB);
	bdFree(&YB);
	
	bdFree(&resultA);
	bdFree(&resultB);
	bdFree(&resultC);
	bdFree(&FIN);


	return 0;
}

```

## LamdaDiffBig (hader)

```C
printf("Test Lambda Diff\n\r");
	
	BB RESULT, MOD, Xi, Yi, Xj, Yj;
	
	RESULT = bdNew();
	MOD = bdNew();
	Xi = bdNew();
	Yi = bdNew();
	Xj = bdNew();
	Yj = bdNew();
	
	
	bdConvFromHex(MOD, "7");
	bdConvFromHex(Xi, "6");
	bdConvFromHex(Yi, "5");
	bdConvFromHex(Xj, "4");
	bdConvFromHex(Yj, "5");
	
	
	
		
	LamdaDiffBIGD(RESULT, MOD, Xi, Yi, Xj, Yj);
	
	
	bdPrintDecimal("Lambda", RESULT, " \n\r");
	
	
	bdFree(&MOD);
	bdFree(&Xi);
	bdFree(&Yi);
	bdFree(&Xj);
	bdFree(&Yj);

```

## YDiffBIGD - old version

```C

#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");


int YSameBIGD(BB RESULT, BB MOD, BB Lambda, BB X, BB Y, BB X_k)
{

	BB modulus, lambda, x, y, x_k;
	BB resultA, resultB, resultC, FIN;    // auxiliary
	
	assert(RESULT && MOD && Lambda && X && Y && X_k);
	
	modulus = bdNew();
	lambda = bdNew();
	x = bdNew();
	y = bdNew();
	x_k = bdNew();
	
	resultA = bdNew();
	resultB = bdNew();
	resultC = bdNew();
	FIN = bdNew();
	
	
	bdSetEqual(modulus, MOD);
	bdSetEqual(lambda, Lambda);
	bdSetEqual(x, X);
	bdSetEqual(y, Y);
	bdSetEqual(x_k, X_k);
	

	bdSubtract(resultA, x, x_k);
	
	bdMultiply(resultB, lambda, resultA);
	
	bdSubtract(resultC, resultB, y);
	
	bdModulo(FIN, resultC, modulus);

	
		bdFree(&modulus);
		bdFree(&lambda);
		bdFree(&x);
		bdFree(&y);
		bdFree(&x_k);
		
		bdFree(&resultA);
		bdFree(&resultB);
		bdFree(&resultC);
		bdFree(&FIN);

	return 0;
}
```
