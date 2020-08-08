# BigN componets

```C
volatile BIGD pole[10];
pole[0]= bdNew();
pole[5]= bdNew();
bdSetShort(pole[0], 25)
```

## Obnoveni bloku po vyprazdneni
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


## BIG Array

```C
BIGD u, v, w;
	volatile BIGD pole[10];
	
	

	/* Display the BigDigits version number */
	printf("BigDigits version=%d\n\r", bdVersion());

	/* Create new BIGD objects */
	u = bdNew();
	v = bdNew();
	w = bdNew();
	pole[0]= bdNew();
	pole[5]= bdNew();
	bdSetShort(pole[0], 25);
	bdConvFromHex(pole[5], "deadbeeffacedeadbeeffaceaaadeadbeeffaceaaa");
```
## Appka (Fermat, bdMultiply, bdCompare)

```C
#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

int TestD(){
	
	EMPTYLINE
	EMPTYLINE
	printf("Tototo je test bloku TestD\n\r");


	volatile BIGD pole[10];
	BIGD result;

	/* Create new BIGD objects */
	pole[0]= bdNew();
	pole[5]= bdNew();
	result= bdNew();

	/* Naplneni DEC hodnotami */
	//bdSetShort(pole[0], 25);
	//bdSetShort(pole[5], 35);
	
	/* Naplneni HEX hodnotami */
	bdConvFromHex(pole[0], "dd");
	bdConvFromHex(pole[5], "aa");
	
	EMPTYLINE
	//vypis DEC hodnoty
	bdPrintDecimal("Pole DEC[5]", pole[0], "\n\r");
	bdPrintDecimal("Pole DEC[5]", pole[5], "\n\r");
	
	EMPTYLINE
	// vypis HEX hodnoty
	bdPrintHex("Pole HEX[0]", pole[0], "\n\r");
	bdPrintHex("Pole HEX[5]", pole[5], "\n\r");


	int delka;
	uint8_t *array;

	// prevod Big Numberu
	delka = bdConvToOctets(pole[0], NULL, 0);
	array = malloc(delka);
	bdConvToOctets(pole[0], array, delka);


	// prevod Big Numberu
	delka = bdConvToOctets(pole[5], NULL, 0);
	array = malloc(delka);
	bdConvToOctets(pole[5], array, delka);
	
	
	/// MULTIPLY
	//bdMultiply(result, pole[0], pole[5]);
	
	/// Add
	bdAdd(result, pole[0], pole[5]);



	/* Display the result */
	bdPrintHex("0x", pole[0], " * ");
	bdPrintHex("0x", pole[5], " = ");
	bdPrintHex("0x", result, "\n\r");
	
	EMPTYLINE
	/* and again in decimal format */
	bdPrintDecimal("", pole[0], " * ");
	bdPrintDecimal("", pole[5], " = ");
	bdPrintDecimal("", result, "\n\r");


	// Comparsion two arrays

	int testCOMP = bdCompare(pole[0], pole[5]);

	printf("\n\rCislo rozdilu je %d\n\r", testCOMP);
	
	
	
	bdFree (&pole[0]);
	bdFree (&pole[5]);
	bdFree (&result);
	
	return 0;

}
```

## Big Array [10], for, 

```C
#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

int TestE(){
	
	EMPTYLINE

	volatile BIGD pole[10];

	for(int i = 0; i < 10; i++){
		
		//printf("Test %d\n\r", i);
		pole[i]= bdNew();
	}
	
	for(int i = 0; i < 10; i++){
		bdConvFromHex(pole[i], "dd");
	}
	
	int delka;
	uint8_t *array;
	
		for(int i = 0; i < 10; i++){
			// prevod Big Numberu
			delka = bdConvToOctets(pole[i], NULL, 0);
			array = malloc(delka);
			bdConvToOctets(pole[i], array, delka);
		}
		
		for(int i = 0; i < 10; i++){
			
			EMPTYLINE
			printf("Cislo poradi %d =>\n\r", i);
			bdPrintDecimal("DEC ", pole[i], "\n\r");
			bdPrintHex("HEX ", pole[i], "\n\r");
		}
				
		EMPTYLINE
		for(int i = 0; i < 10; i++){
	
			printf("Mazu %d \n\r", i);
			bdFree (&pole[i]);
		}
		
		EMPTYLINE		
		for(int i = 0; i < 10; i++){
			
			EMPTYLINE
			printf("Cislo poradi %d =>\n\r", i);
			bdPrintDecimal("DEC ", pole[i], "\n\r");
			bdPrintHex("HEX ", pole[i], "\n\r");
		}
		
		
	return 0;
}
```
