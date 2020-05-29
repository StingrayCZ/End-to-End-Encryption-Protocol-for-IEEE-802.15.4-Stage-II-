## Konzultace 29.5.2020

### 1.Issue - Migrace proměnných

Aplikace na výměnu klíčů je rozdělena do blok;, které jsou typu **int nazev(){}** nebo **void nazev(){}**. V případě první se hodnoty vrací pomocí return. V případě druhého typu se hodnoty vrací pomocí pointerů.

Pokud je podprogram je typu int a vrací hodnotu přes return, aplikace funguje správně. V příkladu níže je test o test generátoru pseudonáhodných čísel, který v další fázi prochází "přiškrcením" přes funkci modulo, která jej omezí na rozsah 1-300. Níže je ukázka obou varianta. První dvě ukázky kódu ukazují, co je v APP_TaskHandleru.. Pod nimi jsou dvě varianty fukce modulo. Jedna vrací vysledek výpočtu přes return (proto v mainu je *TESTRAND = modulo(&TESTRAND, &mod);*), druhá vrací výsledek přes pointer (proto v mainu je *moduloVOID(&TESTRAND, &mod, &result);*, kde *&result* je proměnná, kam se uloží výsledek z podpogramu).

Všechny tuto funkce jsou zaneseny v knihovně, k náhledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/ECDH%20inSTACK/ECDH_Functions.h">zde</a>.

**Otázka: Je v AVR Studiu problém s návratem výsledku z podprogramu typu void. V CodeBlock ani v jiném editoru jsem se s podobným problémem nesetkal.**
```c
///Varianta pro 
static void APP_TaskHandler(void)
{
	
	#ifdef USB_DEBUG
	mod = 50;
	TESTRAND = rand();
	TESTRAND = modulo(&TESTRAND, &mod);
	printf("\r\nRandom cislo je %d",TESTRAND);
	#endif

}
```

```c
static void APP_TaskHandler(void)
{
	
	#ifdef USB_DEBUG
	mod = 50;
	TESTRAND = rand();
	moduloVOID(&TESTRAND, &mod, &result);
	printf("\r\nRandom cislo je %d",result);
	#endif

}
```

```c
//////////////////////////////////
//// MODULO //////////////////////
//////////////////////////////////f
int modulo (long *num, long *mod)
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
//// VOID MODULO //////////////////////
//////////////////////////////////
void moduloVOID (long *num, long *mod, long *result)
{

	long tempNum = *num;

	if(tempNum > 0) // Je kladne
	{
		tempNum %= *mod;    // Vypocet modula

		*result = tempNum;     // Navrat vypocitane hodnoty cyklu
	}

	else if(tempNum < 0)  // Je zaporne
	{
		tempNum *= (-1);  // uprava cisla zpet na kladne

		tempNum %= *mod;  // Vypocet modula

		tempNum = *mod - tempNum;  // Specialni uprava pro zaporne cislo

		*result = tempNum;     // Navrat vypocitane hodnoty cyklu
	}

}
```

### 2.Issue - návěstí

**Otázka:** Pokud chci docílit postupného zapínání odesílání jenotlivých payloadů v části kódu **static void APP_TaskHandler(void)**, je vhodnější použít návěstí (*viz idea níže*) než přepínání stavů pomocí **swtich**? V případě použití switch mi to nepřepíná.

```c
 int number = 50;
  

    if (number > 10){
        goto black;
    }
    else{
        
         printf("\nCislo je mensi nez 10");
         return;
    }
    
   
black:
    
    if (number > 20){
        goto white;
    }
    else{
        printf("\nCislo je vetsi nez 10, ale mensi nez 20");
    
        return;
    }

white:
    printf("\nJe versi nez 20");
    return;
}
```

### 3.Issue - obsah práce

Z důvodu, že jsem student oboru infomační bezpečnosti bych věnoval bych hlavní pozornost na můj algoritmus na výměnu klíčů.

**Otázka:** Souhlasíte s níže obecným návrhem. To bych měl stihnout do pondělní konzultace. Aplikace pro výmněu klíče funguje skvěle (v codeBlocks), s jejím popisem nebude problém. **V pondělí bych chtěl řešit odesílání dat do sítě internet**.

* Obecný popis algoritmu (Vývojový diagram), koncept textu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/OverLeaf/KeyExchangeconcept.pdf">zde</a>
* Detailní popis jeho částí a z důvodnění, proč jsem tu kterou část vytvořil zrovna tak
* Pak bych se separátně věnoval implementaci aplikace pro výměnu klíčů do stacku. Aplikace je řešena modulárně, např. níže je volání části, která sama pomocí randomních čísel zvolí a otestuje vstupní hodnoty a následně provede výpočet grupy eliptické křivky, kterou následně zkontroluje. Až poté vrátí výsledekv podobně prvního bodu grypy a řádu grupy. *Prozatimním problémem je výše popsaný problém s **void** *.

```c
ObtainPointComplex(&mod, &a, &b, &X, &Y, &O);

printf("\r\nVstupni hodnoty jsou: mod = %d, parametry jsou %d a %d", mod, a, b);
printf("\r\n[%d, %d], Order is %d", X, Y, O)
```
