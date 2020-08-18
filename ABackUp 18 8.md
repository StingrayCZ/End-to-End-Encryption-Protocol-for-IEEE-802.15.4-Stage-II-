# BackUP 18.8.2020

```C
	//
	//printf("Test Lambda Diff\n\r");
	//
	//BB RESULT, MOD, Lambda, X, Y, X_k;
	//
	//RESULT = bdNew();
	//MOD = bdNew();
	//X = bdNew();
	//Y= bdNew();
	//Lambda = bdNew();
	//X_k = bdNew();
	//
	//
	//bdConvFromHex(MOD, "b");
	//bdConvFromHex(Lambda, "5");
	//bdConvFromHex(X, "a");
	//bdConvFromHex(Y, "2");
	//bdConvFromHex(X_k, "2");
		//
	//YUniBIGD(RESULT, MOD, Lambda, X, Y, X_k);
	//bdPrintDecimal("Resulcft ", RESULT, " \n\r");
	//
	//
	//bdFree(&MOD);
	//bdFree(&X);
	//bdFree(&Y);
	//bdFree(&X_k);
	//bdFree(&Lambda);
	//
	//
	//EMPTYLINE
	
	//////////////////////////////////////////////////////////////////////////////
	
	//printf("Point comp appk \n\r");
	//
	//
	//BB  X,  Y, a, mod, ResultX, ResultY;
	//
	//
	//X = bdNew();
	//Y = bdNew();
	//a = bdNew();
	//mod = bdNew();
	//
	//ResultX = bdNew();
	//ResultY = bdNew();
//
	//bdConvFromHex(X, "1");
	//bdConvFromHex(Y, "6");
	//bdConvFromHex(a, "1");
	//bdConvFromHex(mod, "7");
	//
	//uint32_t iteration = 11;
	//uint8_t STOPval;
	//
	//
	//PointCompBIGD(X, Y, a, mod, ResultX, ResultY, &iteration, &STOPval);
	//
	//bdPrintDecimal("Xmain ", ResultX, " \n\r");
	//bdPrintDecimal("Ymain ", ResultY, " \n\r");
	//
	//printf("cislo stopval je %d \n\r", STOPval);
	//
	//
	//bdFree(&X);
	//bdFree(&Y);
	//bdFree(&a);
	//bdFree(&mod);
	//
	//bdFree(&ResultX);
	//bdFree(&ResultY);
	
	
	//////////////////////////////////////////////////////////////////////////
	
	//printf("Napis vysledek \n\r");
	//
	//BB Xi, Yi, Xj, Yj;
	//
	//uint8_t RESULT;
	//
	//Xi = bdNew();
	//Yi = bdNew();
	//Xj = bdNew();
	//Yj = bdNew();
	//
	//bdConvFromHex(Xi, "5");
	//bdConvFromHex(Yi, "1");
	//bdConvFromHex(Xj, "5");
	//bdConvFromHex(Yj, "1");
	//
	//RecogniserBIGD(&RESULT, Xi, Yi, Xj, Yj);
	//
	//printf("Napis vysledek %d \n\r", RESULT);
	//
	//
	//bdFree(&Xi);
	//bdFree(&Yi);
	//
	//bdFree(&Xj);
	//bdFree(&Yj);
	
	//////////////////////////////////////////////////////////////////////////
	
	//BB RESULT, MOD, Lambda, Xi, Xj;
	//
	//RESULT = bdNew();
	//MOD = bdNew();
	//Lambda = bdNew();
	//Xi = bdNew();
	//Xj = bdNew();
	//
	//bdConvFromHex(MOD, "11");
	//bdConvFromHex(Lambda, "0");
	//bdConvFromHex(Xi, "0");
	//bdConvFromHex(Xj, "8");
	//
	//
	//XDiffBIGD(RESULT, MOD, Lambda, Xi, Xj);
	//
	//bdPrintDecimal("XDiffMain ", RESULT, " \n\r");
	//
	//bdFree(&RESULT);
	//bdFree(&MOD);
	//bdFree(&Lambda);
	//bdFree(&Xi);
	//bdFree(&Xj);
	
	//////////////////////////////////////////////////////////////////////////
	
	//BB RESULT, MOD, Lambda, X, Y, X_k;
	//
	//RESULT = bdNew();
	//MOD = bdNew();
	//Lambda = bdNew();
	//X = bdNew();
	//Y = bdNew();
	//X_k = bdNew();
	//
	//
	//bdConvFromHex(MOD, "11");
	//bdConvFromHex(X, "5");
	//bdConvFromHex(Lambda, "d");
	//
	//bdConvFromHex(Y, "1");
	//bdConvFromHex(X_k, "5");
	//
	//
	//YUniBIGD(RESULT, MOD, Lambda, X, Y, X_k);
	//
	//
	//
	//bdPrintDecimal("YUniMain ", RESULT, " \n\r");
	//
	//bdFree(&RESULT);
	//bdFree(&MOD);
	//bdFree(&Lambda);
	//bdFree(&X);
	//bdFree(&Y);
	//bdFree(&X_k);
	
	//////////////////////////////////////////////////////////////////////////
	//
	//printf("VERIFY \n\r");
	//
	//uint8_t RESULT;
	//BB modulus, X, Y, a, b;
	//
	//
	//modulus = bdNew();
	//X = bdNew();
	//Y = bdNew();
	//a = bdNew();
	//b = bdNew();
	//
	//
	//bdConvFromHex(modulus, "7");
	//bdConvFromHex(X, "1");
	//bdConvFromHex(Y, "1");
	//bdConvFromHex(a, "1");
	//bdConvFromHex(b, "7");
	//
	//
	//VerifyOfPointBIGD(&RESULT, modulus, X, Y, a, b);
	//
	//printf("Vysledek je %d \n\r", RESULT);
	//
	//bdFree(&modulus);
	//bdFree(&X);
	//bdFree(&Y);
	//bdFree(&a);
	//bdFree(&b);
	
	
	//////////////////////////////////////////////////////////////////////////
	
	//printf("Ladeni aplikace checkValABBIGD \n\r");
	//
	//uint8_t TESTvalue;
	//
	//BB MOD, A, B;
	//
	//MOD = bdNew();
	//A = bdNew();
	//B = bdNew();
	//
	//
	//bdConvFromHex(MOD, "7");
	//bdConvFromHex(A, "2");
	//bdConvFromHex(B, "2");
	//
	//checkValABBIGD(&TESTvalue, MOD, A, B);
	//
	//printf("Test Value (main) is %d \n\r", TESTvalue);
	//
	//
	//bdFree(&MOD);
	//bdFree(&A);
	//bdFree(&B);
	//
	
	///////////////////////////////////////////////////////////////////////////
	//
	//printf("Ladeni aplikace XPartBIGD \n\r");
	//
	//
	//BB P, A, B;
	//BB nums[100];
	//
	//P = bdNew();
	//A = bdNew();
	//B = bdNew();
	//
	//bdConvFromHex(P, "7");
	//bdConvFromHex(A, "1");
	//bdConvFromHex(B, "6");
	//
	//for(int8_t i = 0; i <= 100; i++)
	//{
		//nums[i] = bdNew();
	//}
	//
		//
	//XPartBIGD(P, A, B, nums);
//
//
		//
		//bdPrintDecimal("Pole MAIN 0 ", nums[0], " \n\r");
		//bdPrintDecimal("Pole MAIN 1 ", nums[1], " \n\r");
		//bdPrintDecimal("Pole MAIN 2 ", nums[2], " \n\r");
		//bdPrintDecimal("Pole MAIN 3 ", nums[3], " \n\r");
		//bdPrintDecimal("Pole MAIN 4 ", nums[4], " \n\r");
		//bdPrintDecimal("Pole MAIN 5 ", nums[5], " \n\r");
		//bdPrintDecimal("Pole MAIN 6 ", nums[6], " \n\r");
		//bdPrintDecimal("Pole MAIN 7 ", nums[7], " \n\r");
		//bdPrintDecimal("Pole MAIN 8 ", nums[8], " \n\r");
		//
		//
		//for(int8_t i = 0; i <= 100; i++)
		//{
			//bdFree(&nums[i]);
		//}
		//
		//bdFree(&P);
		//bdFree(&A);
		//bdFree(&B);
		//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//printf("Ladeni aplikace YPartBIG \n\r");
	//
	//BB MOD;
	//volatile BB nums[100];
	//
	//MOD = bdNew();
	//
	//for(int8_t i = 0; i <= 100; i++)
	//{
		//nums[i] = bdNew();
	//}
	//
	//bdConvFromHex(MOD, "11");
	//
	//
	//YPartBIGD(MOD, nums);
	//
	//
	//printf("Prenesene vysledky \n\r");
	//for(int8_t i = 0; i <= 100; i++)
	//{
		//bdPrintDecimal("Pole MAIN = ", nums[i], " \n\r");
	//}
	//
	//
	//for(int8_t i = 0; i <= 100; i++)
	//{
		//bdFree(&nums[i]);
	//}
	//
	//bdFree(&MOD);
	//
		//
		
```
