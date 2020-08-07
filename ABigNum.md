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
