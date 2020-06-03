## Konzultace 3.6.2020

PDF práce k nahledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis.pdfp">zde</a>.


Problém s proměnnými vyřešen. Už to ptacuje dobře.

```c
#include <inttypes.h>
#define __STDC_FORMAT_MACROS 1
        printf("\n\rcislo je %d", resultB);
	printf("\n\r%" PRId32 "\n", resultB);
```

## Konzultace 2.6.2020

### Issue 1 - Funkce modulo

Pro můj algoritmus jsem vyřvořil aplikaci k počítání zbytku po dělení (modulo), který pracuje jak s kladnými, tak i zápornými čísly. Ovšem problém nastává tehdy pokud na vstupu je číslo, které je větší než 32,768. Aplikace sice proběhne, ale vrátí špatný výsledek.

Pro testování v AVR jsem si vytvořil stejnou aplikaci, která je přetypována na **uint8_t**. Ta pracuje spolehlivě do hodnoty 255. Výpočet ověřen ve WolframAlpha.

Níže jsou je ukázka **APP_TaskHandleru**(jako main aplikace) a obou verzí aplikace pro počítání modulo.

**Otázka: Jaký typ zvolit nebo jak kó ošetřit? Zkoušel jsem Long, ten sice funguje, ale jeho hodnota nepřechází do jiných částí kódů (pravděpodobně potřeba přetypování všeho)** 

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/Wolf.PNG" width="600" /> 
<p float="left">

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/Putty.PNG" width="600" /> 
<p float="left">
	

```c
static void APP_TaskHandler(void)
{
	int num, mod, resultA, resultB;
	
	printf("\n\rNapis cislo\r\n");
	scanf("%d", &num);
	printf("\n\rNapis modulua\n");
	scanf("%d", &mod);
	
	
	resultikA = TESTmodulo(&num, &mod);
	
	
	resultikB = modulo(&num, &mod);
	
	
	printf("\n\rVyskedek MOD (uint8_t) je %d", resultikA);
	printf("\n\rVyskedek MOD (int) je %d", resultikB);
	
}
```

```c
//////////////////////////////////
//// MODULO //////////////////////
//////////////////////////////////
int modulo (int *num, int *mod)
{

	long tempNum = *num;

	if(tempNum > 0) // Je kladne
	{
		tempNum %= *mod;    // Vypocet modula

		return tempNum;     // Navrat vypocitane hodnoty cyklu
	}

	else if(tempNum < 0)  // Je zaporne
	{
		tempNum *= (-1);  // uprava cisla zpet na kladne

		tempNum %= *mod;  // Vypocet modula

		tempNum = *mod - tempNum;  // Specialni uprava pro zaporne cislo

		return tempNum;    // Navrat vypocitane hodnoty cyklu
	}

	return 0;
}
```

```c
//////////////////////////////////
//// UINT8_T MODULO //////////////////////
//////////////////////////////////f
int TESTmodulo (uint8_t *num, uint8_t *mod)
{

	uint8_t tempNum = *num;

	if(tempNum > 0) // Je kladne
	{
		tempNum %= *mod;    // Vypocet modula

		return tempNum;     // Navrat vypocitane hodnoty cyklu
	}

	else if(tempNum < 0)  // Je zaporne
	{
		tempNum *= (-1);  // uprava cisla zpet na kladne

		tempNum %= *mod;  // Vypocet modula

		tempNum = *mod - tempNum;  // Specialni uprava pro zaporne cislo

		return tempNum;    // Navrat vypocitane hodnoty cyklu
	}

	return 0;
}
```

### Issue 2 - Padding

**Tato aplikace má za úkol provádět dorovnání čísla na 16 místné číslo, tzv. padding.** Postup je takový, že aplikace si spočítá délku vstupu, poté číslo rozdělí do polí po jednotlyvých číslicích a do prázdných míst doplní 1. Potud mi algortimus pracuje správně, ikdyž je tu opět problém pokud je vstup více jako 9 místný. Opět to vrací špatná čísla. Což by navadilo. Vstup z algortimu ECDH nebude nikdy tak velký.

**Hlavním problémem algoritmu je v poslední část algoritmu**, která má na za úkol z pole poskládat opět číslo typu **int**.

**Otázka: Je opět problém s typy proměnných? Jak řešit**

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/padding.PNG" width="300" /> 
<p float="left">


```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EMPTYLINE printf("\n\r");

void Padding();


int main()
{
    static int num, result;

    while (1){

    printf("\n\rZadej hondotu:\n\r");
    scanf("%d", &num);


    Padding(&num, &result);


    }
}


void Padding(int *num, int *res)
{


    static int number, size;
    static int i;
    static int result;
    int array[16];   // storage for numbers

    number = *num;
    size = 0;

    // Computing how many positions it has
    while (number != 0)
    {
        number /= 10;
        size++;
    }

    // when result is 0, this is considered as position 1
    if (size == 0)
    {
        size = 1;
    }

    printf("\nCislo obsazuje %d", size);

    size -= 1; // array starts from 0

    // DIVISION ARRAY INTO INDIVIDUAL DIGITS
    number = *num;

    i = size;



    while (number != 0)
    {
        array[i] = number % 10;
        number /= 10;
        i--;
    }

    // Test Print
//    for(int j = size; j >= 0; j--)
//    {
//        printf("\n\rpole [%d] = %d", j, array[j]);
//    }


    // PADDING
    for(int k = (size + 1); k < 16; k++){

        array[k] = 1;
    }


    EMPTYLINE

    // Test Print
    for(int t = 0; t < 16; t++)
    {
        printf("\n\rpole [%2d] = %d", t, array[t]);
    }
    
    //////////////////
    // Skladani cisla
    for (int g = 0; g < 15; g++){
        result = 10 * result + array[g];
    }

    EMPTYLINE

    printf("\n\rNum is %d", result);

}

```


