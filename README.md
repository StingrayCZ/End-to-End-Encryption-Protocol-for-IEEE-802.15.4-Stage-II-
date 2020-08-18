# Konzultace 18.8.2020

```C
// Faze A
BB MOD, a_parameter, b_parameter;
volatile BB resultsA[2];

// Faze B 
BB Order, Xf, Yf;
volatile BA results[];
volatile BB results[];

// Faze C
BB Xm, Ym, Xo, Yo, KEY;

MOD = bdNew();
a_parametr = bdNew();
b_parametr = bdNew();
resultsA[0] = bdNew();
resultsA[1] = bdNew();
resultsA[2] = bdNew();
Order = bdNew();
Xf = bdNew();
Yf = bdNew();

resultsBA[0] = bdNew();
resultsBA[1] = bdNew();
resultsBA[2] = bdNew();

resultsBB[0] = bdNew();
resultsBB[1] = bdNew();
resultsBB[2] = bdNew();

Xm = bdNew();
Ym = bdNew();
Xo = bdNew();
Yo = bdNew();
KEY = bdNew();

ECDH_PHASE_A_BIGD(MOD, a_parameter, b_parameter, resultsA)
```

```C
BB Oder, 

// Face B (deska A)
ECDH_PHASE_BA_BIGD(Order, Xf, Yf, a_parameter, MOD, BB resultsBA);
```



```C
// Face B (deska B)
ECDH_PHASE_BB_BIGD(MOD, a_parameter, b_parameter, resultsBB);
```

```C
// Face C
ECDH_PHASE_C_BIGD(Xm, Ym, Xo, Yo, MOD, a_parameter, BB KEY);
```

# Konzultace 17.8.2020

## 1 # Otazka
Mam problem s funkci preudonahodneho cisla. Jednak mi nefunguje původní funkce ***my_rand***, která má ovšem tu nevýhodu, že pořád dokola dává stejnou hodnotu. K manualu je primo napsane, ze je mozne k funlci primo napojit vlastni **random** funkci. <br/>

Níže je pokus, jak implementovat funkci **PHY_RandomReq()**, ktery ovsem nefunguje.

```C
BIGD a;

mod = bdNew();

bdRandomSeeded(mod, 128, (const unsigned char*)"", 0, my_rand);  // 518 bits key

bdPrintDecimal("mod = ", a, " \n\r");

```

```C
int my_rand(unsigned char *bytes, size_t nbytes, const unsigned char *seed, size_t seedlen)
	/* Our own (very insecure) random generator call-back function using good old rand()
	This demonstrates the required format for BD_RANDFUNC
	-- replace this in practice with your own cryptographically-secure function.
	*/
	{
		unsigned int myseed;
		size_t i;
		int offset;

		/* Use time - then blend in seed, if any */
		myseed = (unsigned)time(NULL);
		if (seed)
		{
			for (offset = 0, i = 0; i < seedlen; i++, offset = (offset + 1) % sizeof(unsigned))
			myseed ^= ((unsigned int)seed[i] << (offset * 8));
		}
		
	
		srand(myseed);
		while (nbytes--)
		{
			*bytes++ = rand() & 0xFF;
		}

		return 0;
	}
```

```C
void randomize(void)
  {
     srand(PHY_RandomizeReq());
 }


bdRandomSeeded(mod, 128, (const unsigned char*)"", 0, randomize);
```


## 2 # Otazka
Pomoci prikazu **for** aplikace porovnava hodnoty Xove a Yove tabulky a tak urci prvni bod. Ovsem je zde problem pokud bude modulo velke, tim vzroste i pocet moznych bodu (iteraci), coz je pro cyklus **for** neunosne.

Z toho vychazi, ze grupa lze vytvorit s velkymi hodnotami pro asymptory **a** a **b**, ale s mayl ciselm modulo, tak do hodnoty 1000. Je to i z dovodu rychlosti aplikace. **Je to tak mozne nechat?**

```C
for(uint32_t  k = 0; k <= X_iter; k++)  // Give X's
	{
		for(uint32_t  i = 0; i <= Y_iter; i++)  // Give Y's
		{
			
			compareA = bdCompare(poleA[i], poleB[i]);
			
```
