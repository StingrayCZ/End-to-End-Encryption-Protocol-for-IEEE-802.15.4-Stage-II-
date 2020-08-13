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
