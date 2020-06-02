# Historical Content of Consultations

## Konzultace 1.6.2020

Stack v2020 k náhledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Protocol%20Stack%20v2020.zip">zde</a>.

### Security
```c
NWK_SetSecurityKey((uint8_t *)"Security12345678");
```
### Endpoints
```c
static bool appDataInd(NWK_DataInd_t *ind) 
{ 
  // process the frame 
  return true; 
} 
 
NWK_OpenEndpoint(1, appDataInd);  
```

### Payload
```c
static uint8_t message; 
static NWK_DataReq_t nwkDataReq; 
 
static void appDataConf(NWK_DataReq_t *req) 
{ 
  if (NWK_SUCCESS_STATUS == req->status) 
    // frame was sent successfully 
  else 
    // some error happened 
} 
 
static void sendFrame(void) 
{ 
  nwkDataReq.dstAddr = 0; 
  nwkDataReq.dstEndpoint = 1; 
  nwkDataReq.srcEndpoint = 5; 
  nwkDataReq.options = NWK_OPT_ACK_REQUEST | NWK_OPT_ENABLE_SECURITY; 
  nwkDataReq.data = &message; 
  nwkDataReq.size = sizeof(message); 
  nwkDataReq.confirm = appDataConf; 
  NWK_DataReq(&nwkDataReq); 
} 
```
  
### Receiving the Data

```c
static bool appDataInd(NWK_DataInd_t *ind) 
{ 
  if (!appReadyToReceive) 
    return false; 
  // process ind->size bytes of the data pointed by ind->data 
  NWK_SetAckControl(APP_DO_NOT_SLEEP); 
  return true; 
} 
```
```c
Table 5-4. Network Data Indication Structure Fields 
Name Description 
srcAddr Network address of the source
dstEndpoint Destination endpoint number (
srcEndpoint Source endpoint number (remote
Options Data indication options. It may
Table 5-5 (combined using bitwise
Data Pointer to the payload data 
Size Size of the payload data 
Lqi LQI of the received frame 
Rssi RSSI of the received frame 

Table 5-5. Data Indication Options 
Name Description 
NWK_IND_OPT_ACK_REQUESTED       Acknowledgment was requested 
NWK_IND_OPT_SECURED             Frame was encrypted 
NWK_IND_OPT_BROADCAST           Frame was sent to a broadcast address (0xffff) 
NWK_IND_OPT_LOCAL               Frame was received from a directly accessible node 
NWK_IND_OPT_BROADCAST_PAN_ID    Frame was sent to a broadcast PAN ID (0xffff) 
NWK_IND_OPT_LINK_LOCAL          Frame was sent with a Link Local field set to 1 
NWK_IND_OPT_MULTICAST           Frame was sent to a group address 

```

### Timers
```c
static SYS_Timer_t appTimer; 
 
static void appTimerHandler(SYS_Timer_t *timer) 
{ 
  // handle timer event 
  If (timeToStop) 
    SYS_TimerStop(timer); 
} 
 
static void startTimer(void) 
{ 
  appTimer.interval = 1000; 
  appTimer.mode = SYS_TIMER_PERIODIC_MODE; 
  appTimer.handler = appTimerHandler; 
  SYS_TimerStart(&appTimer); 
} 
```


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

**Otázka:** Souhlasíte s níže vypsaným obecným návrhem obsahu práce? Ten bych měl stihnout do pondělní konzultace vložit přímo do dokumentu práce (v Latexu). Aplikace pro výmněu klíče funguje skvěle (v codeBlocks), s jejím popisem nebude problém. **V pondělí bych chtěl řešit odesílání dat do sítě internet**.

* Obecný popis algoritmu (Vývojový diagram), koncept textu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/OverLeaf/KeyExchangeconcept.pdf">zde</a>
* Detailní popis jeho částí a z důvodnění, proč jsem tu kterou část vytvořil zrovna tak
* Pak bych se separátně věnoval implementaci aplikace pro výměnu klíčů do stacku. Aplikace je řešena modulárně, např. níže je volání části, která sama pomocí randomních čísel zvolí a otestuje vstupní hodnoty a následně provede výpočet grupy eliptické křivky, kterou následně zkontroluje. Až poté vrátí výsledekv podobně prvního bodu grypy a řádu grupy. *Prozatimním problémem je výše popsaný problém s **void** *.

```c
ObtainPointComplex(&mod, &a, &b, &X, &Y, &O);

printf("\r\nVstupni hodnoty jsou: mod = %d, parametry jsou %d a %d", mod, a, b);
printf("\r\n[%d, %d], Order is %d", X, Y, O)
```


---------------------------------------------------------------------------------------------------------------------------
## From 25.5.2020
 
• Algoritmus na výměnu klíču je hotov. Ukázka části pro generování (obsauje i zpětnou kontrolu vygenerované grupy) <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Prototype%2025.5.2020.md">zde</a>.</p>
• Ukázka aplikace pro výpočet společného bodu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Prototype%2025.5.2020%20(mutual%20point).md">zde</a>.</p>
• Spustitelná výměna klíčů (manuální vstup) v .exe formátu ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/KeyExchange%20app.exe">zde</a>.</p>
• Spustitelná výměna klíčů (psaudorandom vstup) v .exe formátu ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Points%20Generator%20(AUTO).exe">zde</a>.</p>
• Oproti algoritmu ze zimního semestru funguje s jakýmkoliv vstupem (nehodící vstupy jsou automaticky sortovány pomocí podmínek)</p>
• Je kompletně vytvořen softwaru CodeBlocks. Je ale koncipován modulárně, není problém jej snadno přenést do stacku (mám již vyzkoušeno), v pondělí budu prezentovat</p>

• Na případné podělní konzultaci bych rád pořešil komunikaci sítě 802.15.4 se sítí internet.</p>

## Flowchart Diagram výměny klíčů (zelená pole jsou hotova a odzkoušena)
Pro prvotní výměnu vstpu, bude nutné zvolit **implicitní tajný klíč** pro AES blok.

<p float="left">
  <img src="/Pictures (general)/ECDH flowchart 2020_1.png" width="600" /> 
<p float="left">
 
<p float="left">
  <img src="/Pictures (general)/ECDH Flowchart SUPER.png" width="600" /> 
<p float="left">

## Generování bodů (na základě modula a parametrů a a b)
Toto je starší verze s "manuálním" vstupem hodnot.
<p float="left">
  <img src="/Pictures (general)/ECHD.PNG" width="350" /> 
<p float="left">
 
 ## Psudonáhodné vstupy
Generování pseudonáhodných vstupů na základě času (v další verzi zaměním za generátor přímo z LWM). Proměnná throttle má za úkol omezovat pseudonáhodná čísla v rozsahu 0 - 300. Algoritmus je testován i na 2000. Funguje, nicméně generování klíčů je pomalejší, resp. čas je více proměnlivý (dle náhodně zvoleného vstupu).

```sh
// Generator of random numbers
    srand((unsigned int) time(NULL));
    int Throttle = 300;                 // Throttle of power
```
```sh
a = rand() % Throttle;
b = rand() % Throttle;
```

## Návěstí (dotaz na konzultaci)
```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 5;


    if (number > 10)
    {
        goto SEND_ACK;
    }
    if (number > 20)
    {
        goto SEND_MESSAGE;
    }
    else
    {
        goto SEND_END;
    }


SEND_ACK:

    printf("\nCislo je vetsi nez 10, ale mensi nez 20");
    return 0;

SEND_MESSAGE:
    printf("\nJe versi nez 20");
    return 0;


SEND_END:
    printf("\nCislo je mensi nez 10");
    return 0;

}
```

## Prezentace
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_01.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_02.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_03.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_04.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_05.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_06.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_07.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_08.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_09.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_10.png" width="900" /> 
<p float="left">
    
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_11.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_12.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_13.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_14.png" width="900" /> 
<p float="left">
  
  
  
  
  
  
