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
