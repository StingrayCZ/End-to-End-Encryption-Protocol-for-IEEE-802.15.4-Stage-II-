## Konzultace 2.6.2020

### Funkce modulo


Pictures (general)/Cons 2.6.2020/

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/Putty.PNG" width="600" /> 
<p float="left">
	
<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/Wolf.PNG" width="600" /> 
<p float="left">

Pro můj algoritmus jsem si vyřvořil aplikaci k počítání zbytku po dělení (modulo), který pracuje jak s kladnými, tak i zápornými čísly. Ovšem problém nastává tehdy pokud na vstupu je číslo, které je větší než 32,768. Aplikace sice proběhne, ale vrátí špatný výsledek.

Pro testování v AVR jsem si vytvořil stejnou aplikaci, která je přetypována na **uint8_t**. Ta pracuje spolehlivě do hodnoty 255.

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
