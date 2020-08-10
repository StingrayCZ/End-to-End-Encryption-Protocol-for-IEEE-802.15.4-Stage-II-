## BackUp

```C
BIGD Numa, Numx, Numm;
	 
	 Numa = bdNew();
	 Numx = bdNew();
	 Numm = bdNew();
	 
 
	 bdSetShort(Numx, 37);
	 bdSetShort(Numm, 5);
	 
	 bdModSquare(Numa, Numx, Numm);
	 
	 
	 bdPrintHex("Vysledek je 0x", Numa, "\n");
	 bdPrintDecimal("", Numa, "\n");             // Decimalni cislo
	 
	 printf("Vysledek je %d\n", Numa);
	
	///////////////////////////// by Krajsa
	//BIGD u, v, w;
//
	///* Display the BigDigits version number */
	//printf("BigDigits version=%d\n\r", bdVersion());
//
	///* Create new BIGD objects */
	//u = bdNew();
	//v = bdNew();
	//w = bdNew();
//
	///* Compute 2 * 0xdeadbeefface */
	//bdSetShort(u, 2);
	//bdConvFromHex(v, "deadbeeffacedead");
	//bdMultiply(w, u, v);
	//bdPrintDecimal("napis decimalku ", w, " \n\r");
	//
	//int delka = bdConvToOctets(v, NULL, 0);
	//uint8_t pole[20];
	//uint8_t *pole2;
	//pole2 = malloc(delka);
	//
	//bdConvToOctets(v, pole, delka);
	////bdPrintHex("TT0x", v, " \n\r");
	////printf("\n\r");
	//
	//
	//printf("delka = %d\n\r", delka);
	//printf("pole[0] = %d\n\r", pole[0]);
	//printf("pole[1] = %d\n\r", pole[1]);
	//printf("pole[2] = %d\n\r", pole[2]);
	//printf("pole[3] = %d\n\r", pole[3]);
	//
	//bdConvToOctets(v, pole2, delka);
//
	///* Display the result */
	//bdPrintHex("", u, " * ");
	//bdPrintHex("0x", v, " = ");
	//bdPrintHex("0x", w, "\n\r");
	///* and again in decimal format */
	//bdPrintDecimal("", u, " * ");
	//bdPrintDecimal("", v, " = ");
	//bdPrintDecimal("", w, "\n\r");
//
    //bdConvFromHex(v, "deadbeeffacedeadbeeffaceaaadeadbeeffaceaaa");
	//bdConvFromHex(u, "deadbeeffaceaaadeadbeeffaceaaa");
    //bdMultiply(w, u, v);
	//
	///* Display the result */
	//bdPrintHex("0x", u, " * ");
	//bdPrintHex("0x", v, " = ");
	//bdPrintHex("0x", w, "\n\r");
	///* and again in decimal format */
	//bdPrintDecimal("", u, " * ");
	//bdPrintDecimal("", v, " = ");
	//bdPrintDecimal("", w, "\n\r");
//
	///* Free all objects we made */
	//bdFree(&u);
	//bdFree(&v);
	//bdFree(&w);
	//printf("Done, Testing:  \n\r");
	//free(pole2);
	
	///////////////////////////// by Krajsa / END
	
	
	
	/////////////////////////////////////////////
	//printf("\n Toto je testovaci priklad: \n\r");
	//
	//BIGD multA, multB, multT;
	//BIGD quotient, remainder, divident, divisor;
	//
	//quotient = bdNew();
	//remainder = bdNew();
	//divident = bdNew();
	//divisor = bdNew();
	//
	//multA = bdNew();
	//multB = bdNew();
//
	//bdSetShort(multA, 22);
	//bdSetShort(multB, 30);
	//
	//// NASOBENI multT = multA * multB	
	//bdMultiply(divident, multA, multB);
	//
	//
	//bdSetShort(divisor, 2);
	//
	//// DELENI quotient = divident / divisor
	//bdDivide(quotient, remainder, divident, divisor);
	//
	//bdPrintDecimal("Vysledek quotient je ", quotient, "\n\r");
	//bdPrintDecimal("Vysledek remainder je ", remainder, "\n\r");
	//
	//free(quotient);
	//free(remainder);
	//free(divident);
	//free(divisor);
	//
	//free(multA);
	//free(multB);
	//
	
///////////////////////////////////////////////////////////////
	
	BIGD AA, BB, CC;
	int testP;
	
	AA = bdNew();
	BB = bdNew();
	CC = bdNew();
	
	
	bdSetShort(BB, 21);
	bdSetShort(CC, 1);
	
	TEST(AA, BB, CC, &testP);
	
	bdPrintDecimal("Napis hodnotu ", AA, "\n\r");
	printf("Test prvociselnosti je %d \n\r", testP);
	
		
	free(AA);
	free(BB);
	free(CC);
	
	EMPTYLINE
	
	printf("Boca Chica \r\n");
	
	BIGD result, MOD, LAMBDA, X;
	
	result = bdNew();
	MOD = bdNew();
	LAMBDA = bdNew();
	X = bdNew();
	
	bdSetShort(MOD, 7);
	bdConvFromHex(LAMBDA, "6");
	bdSetShort(X, 2);


	XSame(result, MOD, LAMBDA, X);	
	
	bdPrintDecimal("Vysledek Testu DIFF ", result, " \n\r");   // Tisk cisla w
	
	bdFree(&result);
	bdFree(&MOD);
	
	
	printf("RabMiller test \r\n");
	
	TestRB();
  ```
