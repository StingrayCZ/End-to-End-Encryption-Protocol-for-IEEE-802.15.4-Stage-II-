# Konzultace 14.8.2020

Ke stazeni zde <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Stack%2014Aug.zip">zde </a> 

```C
#include <stdio.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

//PointCompBIGD(X, Y, a, mod, &iteration, &STOPval);
//int PointCompBIGD(BB X, BB Y, BB a_asymptote, BB modulus, uint32_t *iteration, int *STOPval)		


int PointCompBIGD(BB X, BB Y, BB a_asymptote, BB modulus, BB ResultX, BB ResultY, uint32_t *iteration, int *STOPval)
{
	
	BB Xi, Yi, Xj, Yj;
	BB mod, a, lambda;
	
	BB resultBigA, resultBigB, resultBigC;
	
	uint32_t repeat, result; 
	
	assert(X && Y && a_asymptote && modulus && ResultX && ResultY);

	
	Xi = bdNew();
	Yi = bdNew();
	Xj = bdNew();
	Yj = bdNew();
	
	mod = bdNew();
	a = bdNew();
	lambda = bdNew();	
	
		
	resultBigA = bdNew();	
	resultBigB = bdNew();
	resultBigC = bdNew();
	
	
	bdSetEqual(Xi, X);
	bdSetEqual(Yi, Y);
	
	bdSetEqual(Xj, Xi);
	bdSetEqual(Yj, Yi);

	
	bdSetEqual(a, a_asymptote);
	bdSetEqual(mod, modulus);
	
	
	// Value for number of iteration
	repeat = *iteration;	
	

	for(uint32_t i = 1; i <= repeat - 2; i++)
	{
		RecogniserBIGD(&result, Xi, Yi, Xj, Yj);
		
		printf("Napis  rozpoznan %d ", result);

		if(result == 1)
		{
			LamdaSameBIGD(resultBigA, mod, Xi, Yi, a);
			
			bdPrintDecimal("Lambda SAME = ", resultBigA, " \n\r");	
			
			XSameBIGD(resultBigB, mod, resultBigA, Xi);
			
			YUniBIGD(resultBigC, mod, resultBigA, Xi, Yi, resultBigB);
			
			
			*STOPval = 1;
			

		}

		else if(result == 2)
		{
			LamdaDiffBIGD(resultBigA, mod, Xi, Yi, Xj, Yj);
			
			bdPrintDecimal("Lmbda Diff = ", resultBigA, " \n\r");	

			
			XDiffBIGD(resultBigB, mod, resultBigA, Xi, Xj);
			
			YUniBIGD(resultBigC, mod, resultBigA, Xi, Yi, resultBigB);
			
			bdPrintDecimal("Xin", resultBigB, " \n\r");
			bdPrintDecimal("Yin", resultBigC, " \n\r");

			*STOPval = 1;
			

		}

		else if(result == 66)
		{
			
			*STOPval = 66;
		}
		
		
		
		bdSetEqual(Xj, resultBigB);	
		bdSetEqual(Yj, resultBigC);	

	}
	
	
	bdPrintDecimal("Xin", resultBigB, " \n\r");
	bdPrintDecimal("Yin", resultBigC, " \n\r");	


	bdSetEqual(ResultX, resultBigB);	
	bdSetEqual(ResultY, resultBigC);	
	
	
	bdFree(&Xi);
	bdFree(&Yi);
	bdFree(&Xj);
	bdFree(&Yj);
	
	bdFree(&mod);
	bdFree(&a);
	bdFree(&lambda);
	
}
```

# Konzultace 13.8.2020

Appka na odecitani, ktera resi problem zaporneho cisla. Pokud je vstup např. **360 - 5** provede se porovnani (**compare = bdCompare(a, b**), zda prvni hodnota je vetsi/mensi. Pokud je vetsi, probehne funkce na odecitani **bdSubstract(a, b);**, pokud je ovšem příklad **5 - 360**, provede se **bdSubstract(b, a);**.

Zaporné číslo zaniká v operaci **Modulo**. Zde v případě záporného vstupu je přidána další operace **bdSubstract**, která číslo invertuje (mod - vysledekMOD = konecny vysledek).

```C

#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

int TestM(){
	
	EMPTYLINE
	
	
	BB a, b, mod;
	BB resultA, resultB, resultC;
	
	int compare;
	
	
	a = bdNew();
	b = bdNew();
	mod = bdNew();
	
	
	resultA = bdNew();
	resultB = bdNew();
	resultC = bdNew();
	
	// 360 - 5 = 355
	//bdConvFromHex(a, "168");  // a = 360
	//bdConvFromHex(b, "5");    // b = 5
	
	
	// 5 - 360 = -355
	bdConvFromHex(a, "5");      // a = 5
	bdConvFromHex(b, "168");    // b = 360
	
	
	bdConvFromHex(mod, "22");  // mod  = 34
	
	compare = bdCompare(a, b);
	
	if(compare == 1){
		
		printf("Priklad 360 - 5 = 355\n\r");		
		bdSubtract(resultA, a, b);   // a - b = kladne cislo
		
		EMPTYLINE
		bdPrintDecimal("A je vetsi, vysledek a - b = ", resultA, " \n\r");
		
		bdModulo(resultB, resultA, mod);
		
		EMPTYLINE
		bdPrintDecimal("Zbytek po deleni kladneho cisla 355", resultB, " \n\r");
		
		
	}
	
	else if(compare == (-1)){
		
		printf("Priklad 5 - 350 = -355\n\r");	
		bdSubtract(resultA, b, a);   // b - a = kladne cislo
		
		EMPTYLINE
		bdPrintDecimal("B je vetsi, vysledek b - a  = ", resultA, " \n\r");
		
		
		bdModulo(resultB, resultA, mod);
		
		bdSubtract(resultC, mod, resultB);
		
		EMPTYLINE
		bdPrintDecimal("Zbytek po deleni zaporneho cisla - 355", resultC, " \n\r");	
		
	}
	
	
	bdFree(&a);
	bdFree(&b);
	bdFree(&mod);
	
	bdFree(&resultA);
	bdFree(&resultB);
	bdFree(&resultC);
	
	
}

```
