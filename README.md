# Konzultace 12.8.2020

Aplikace, ktera ze spoledneho bodu (treba X = 305, Y = 428) nasobenim spocita cislo vetsi nez je 2^127. Reseno pomoci cyklu while/do-while kde uvnitr cyklu je provaden soucin bodu tak dlouho, dokud neni vysledek vetsi ney 2^127 (128 bitove a vetsi cislo).

```C
#include <stdio.h>
#include <string.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");



int TestK(){
	
	// prevod int na BIGD
	BIGD Xseed, Yseed, KeyPattern;
	BIGD resultA, resultB, num;
	
	uint8_t exponent = 127;
	int8_t comparsion;
	
	
	Xseed = bdNew();
	Yseed = bdNew();
	KeyPattern = bdNew();
	
	resultA = bdNew();
	resultB = bdNew();
	num = bdNew();

	int X = 305;            // Spolecny bod X
	int Y = 428;            // Spolecny bod Y
	
		
	bdSetShort(Xseed, X);
	bdSetShort(Yseed, Y);
		
	bdSetShort(num, 2);
	
	

	bdPower(KeyPattern, num, exponent);   // 2^128
	bdDecrement(resultA);
	
	
	
	
	bdPrintDecimal("Velikost klice ", KeyPattern, " \n\r");
	
	
	do{
	
		bdMultiply(resultB, Xseed, Yseed);

		comparsion = bdCompare(resultB, KeyPattern);
		
		
		 bdSetEqual(Xseed, resultB);
		 
		 bdMultiply(resultB, Xseed, Yseed);
		
		
	}while(comparsion != 1);
	
	
	
	
	
	bdPrintDecimal("Vypocitany klic", resultB, " \n\r");
	
	printf("Cislo proovnani %d", comparsion);
	
	
		
	return 0;
	
}
```


# Vlozeni klice do funkce NWK_SetSecurityKey

<p float="left">
  <img src="/Pictures (general)/SecurityA.PNG" width="1500" /> 
<p float="left"> </p>

```C
void NWK_SetSecurityKey(uint8_t *key)
{
  memcpy((uint8_t *)nwkIb.key, key, NWK_SECURITY_KEY_SIZE);
}
```

```C
#define NWK_SECURITY_KEY_SIZE        16
```



