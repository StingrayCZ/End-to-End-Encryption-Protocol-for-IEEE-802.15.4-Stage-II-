# BigN componets

```C
volatile BIGD pole[10];
pole[0]= bdNew();
pole[5]= bdNew();
bdSetShort(pole[0], 25)
```

## obnoveni hodnoty po vyprazdneni
	free(Test);
	
	Test = bdNew();	
	bdSetShort(Test, 23);

## Test
```C
BIGD AA, BB, CC;
	
	AA = bdNew();
	BB = bdNew();
	CC = bdNew();
	
	
	bdSetShort(BB, 13);
	bdSetShort(CC, 3);
	
	TEST(AA, BB, CC);
	
	bdPrintDecimal("Napis hodnotu ", AA, "\n\r");
```

## Comparsion of two numbers (wrong numbers)
```C
	printf("Srovnani dvou velkych cisel\n\r %d \n\r");
	
	BIGD SuperA, SuperB;
	
	SuperA = bdNew();
	SuperB = bdNew();
	
	bdSetShort(SuperA, 50);
	bdSetShort(SuperB, 50);	
	
	if(SuperA > SuperB){
		
		bdPrintDecimal("SuperA s hodnotou ", SuperA, " je vetsi nez SuperB s hodnotou ");
		bdPrintDecimal("", SuperB, " \n\r");
	}
	
	else if(SuperA < SuperB){
		
		bdPrintDecimal("SuperB s hodnotou ", SuperB, " je vetsi nez SuperA s hodnotou ");
		bdPrintDecimal("", SuperA, " \n\r");
		
	}
	
	else if(SuperA == SuperB){
		
		bdPrintDecimal("SuperA s hodnotou ", SuperA, " se rovna s hodnotou SuperB ");
		bdPrintDecimal("", SuperB, " \n\r");
		
	}
```

## Comparsion of two numbers (correct solution)
```C
	BIGD SuperA, SuperB;
	
	int testCOMP;
	
	SuperA = bdNew();
	SuperB = bdNew();
	
	bdSetShort(SuperA, 6800700000);
	bdSetShort(SuperB, 700680070000000);	
	
	
	testCOMP = bdCompare(SuperA, SuperB);
	
	printf("Cislo rozdilu je %d\n\r", testCOMP);	
		
	if(testCOMP == 0){
		
		printf("Cisla jsou stejna \n\r");
	}
	
	else if(testCOMP == 1){
		
		printf("Cislo A je vetsi \n\r");
	}
	
	else if(testCOMP == -1){
		
		printf("Cislo B je vetsi \n\r");
	}
	
	free(SuperA);
	free(SuperB);	
	
```

## Big Numbers (ConvToHex, ConvToOctets)

```C
#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD

int TestB(void){
BB u, v, w;

printf("\n\r");
printf("\n\r");
printf("Tototo je test bloku TestB\n\r");


/* Create new BIGD objects */
u = bdNew();
v = bdNew();
w = bdNew();

bdSetShort(u, 2);
bdConvFromHex(v, "dddaaedfcbbecadadadadadadadadadadedaddaeededadadadaeadad");

//bdConvFromHex(v, "deadbeeffacedead");

bdMultiply(w, u, v);
bdPrintDecimal("Napis Cislo jako DEC ", w, " \n\r");   // Tisk cisla w


int delka = bdConvToOctets(v, NULL, 0);
uint8_t *pole2;
pole2 = malloc(delka);

bdConvToOctets(v, pole2, delka);

/* Display the result */
	bdPrintHex("", u, " * ");
	bdPrintHex("0x", v, " = ");
	bdPrintHex("0x", w, "\n\r");
	/* and again in decimal format */
	bdPrintDecimal("", u, " * ");
	bdPrintDecimal("", v, " = ");
	bdPrintDecimal("", w, "\n\r");
	
	bdFree(&u);
	bdFree(&v);
	bdFree(&w);

return 0;
}
```
