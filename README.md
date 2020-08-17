# Konzultace 17.8.2020

## 1 # Otazka
Mam problem s funkci preudonahodneho cisla. Jednak mi nefunguje původní funkce ***my_rand***, která má ovšem tu nevýhodu, že pořád dokola dává stejnou hodnotu. K manualu je primo napsane, ze je mozne k funlci primo napojit vlastni **random** funkci. <br/>

Níže je pokus, jak implementovat funkci **PHY_RandomReq()**.



```C
bdRandomSeeded(a, 128, (const unsigned char*)"", 0, my_rand);  // 512 bits key

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
```

