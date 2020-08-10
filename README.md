# Konzultace 10.8.2020 - Part II

## Problem s podtecenim
```C

#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");


int TestH(){
	
	
	BB a, b, c, res;
	
	
	a = bdNew();
	b = bdNew();
	res = bdNew();
	
	
	bdConvFromHex(a, "ddddddddddddddddddddddddd");   // 1098630520197798814630476111325
	bdConvFromHex(b, "ddddddddddddddddddd");         // 65483481895792413629917
	 
	
	//bdSetShort(a, 4);
	//bdSetShort(b, 5);
	
	int delka;
	uint8_t *array;
	
	delka = bdConvToOctets(a, NULL, 0);
	array = malloc(delka);
	bdConvToOctets(a, array, delka);
	
	delka = bdConvToOctets(b, NULL, 0);
	array = malloc(delka);
	bdConvToOctets(b, array, delka);

		
	bdSubtract(res, b, a);    // 1098630520197798814630476111325 - 65483481895792413629917 = 1098630454714316918838062481408
	
	
	
	bdPrintDecimal("Vysledek Testu LambdaSAME ", res, " \n\r");
	
	mpPrintDecimalSigned("Vysledek Testu LambdaSAME ", res, " \n\r");
	
	return 0;
}
```

## Data do payloadu

```C
static void appSendData(void)
{
if (appDataReqBusy || 0 == appUartBufferPtr)
return;

memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

appDataReq.dstAddr = 1-APP_ADDR;
appDataReq.dstEndpoint = APP_ENDPOINT;
appDataReq.srcEndpoint = APP_ENDPOINT;
appDataReq.options = NWK_OPT_ENABLE_SECURITY;
appDataReq.data = appDataReqBuffer;
appDataReq.size = appUartBufferPtr;
appDataReq.confirm = appDataConf;
NWK_DataReq(&appDataReq);

appUartBufferPtr = 0;
appDataReqBusy = true;
}
```

```C
volatile BIGD a;
a = bdNew();
bdConvFromHex(a, "dd");

delka = bdConvToOctets(a, NULL, 0);
array = malloc(delka);
bdConvToOctets(a, array, delka);

/* Display the result */
bdPrintHex("0x", a, "\n\r");

/* and again in decimal format */
bdPrintDecimal("", a, "\n\r");

```

## LWM Stack

```C
Možný nástřel TaskHandleru:

static void APP_TaskHandler(void)
{
switch (appState)
{
case APP_STATE_INITIAL:
{
appInit();
appState = APP_STATE_PHASE_A;
} break;

case APP_STATE_PHASE_A:
{
VYPOCTY V PHASE A;
ODESLANI modulu p, a, b; Odeslat klidne ted, nebo stavovym priznakem ve specialni funkci
appState = APP_STATE_PHASE_B;
} break;
case APP_STATE_PHASE_B:
{
VYPOCTY V PHASE B;
Odeslani x, y;
appState = APP_STATE_PHASE_C;
} break;
case APP_STATE_PHASE_C:
{
if(pokud uz prisly data od protejsku){
Vypocty v C;
NWK_SetSecurityKey(NOVY KLIC); pole 128b, idealne;
appState = APP_STATE_IDLE;
}

} break;


case APP_STATE_IDLE:
break;

default:
break;
}
}
```

# Konzultace 10.8.2020

## Test prvociselnosti

Funkce, kde mohu zadat i pocet testů. Ovsem mam problem se zadanim hodnoty **size_t ntests**, zkousel jsem to zadat pomoci cisla (viz nize).

<p float="left">
  <img src="/Pictures (general)/Miller.PNG" width="1500" /> 
<p float="left"> </p>

```
BB a;

a = bdNew();

bdConvFromHex(a, "d");   //13

int bdRabinMiller  ( BIGD  b,  10);   

```

## Problem s podtecenim
<p float="left">
  <img src="/Pictures (general)/NonNeg.PNG" width="1500" /> 
<p float="left"> </p>

Alikace jsem sice predelal, ale problem je s mezivypocty, kterou mohou byt zaponrne. Navrhoval bych implementovat blok s random vyberem klice pomoci BIGN knihovny, s overenim pomoci MillerRabin testu, zbytek by byl stejny (aby to nejak rozumne fungovalo).

# Konzultace 7.8.2020

## Problém s oknem Watch

V okně watch mi to nezpbrazuje hodnotu... V jiném příkladě jsem to vyřešil vypnutím **Optimizace**

<p float="left">
  <img src="/Pictures (general)/Optimization.PNG" width="800" /> 
<p float="left"> </p>

<p float="left">
  <img src="/Pictures (general)/Breakpoint.PNG" width="800" /> 
<p float="left"> </p>

<p float="left">
  <img src="/Pictures (general)/ViewError.PNG" width="1200" /> 
<p float="left"> </p>

## Citace stránky s BIG N... Může to být takhle?
BigDigits multiple-precision arithmetic source code [online]. 2020 [cit. 2020-08-07]. Dostupné z: https://www.di-mgt.com.au/bigdigits.html

## Jak dostat výstup z BIGN do data (payload)?

Předpokládám, že typ **static NWK_DataReq_t appDataReq;**, resp. (**appDataReq.data = data**) asi nestráví **BIG N** proměnnou. 
P5edpoklad generování klíče z kódu níže, výstup **v**.

```C
static void appSendDataRSSItoA401(uint16_t address, uint8_t rssi_i)
{
static uint8_t data[3];

if (appDataReqBusy)
return;

data[0]=address>>8; //first 8 bits from the left
data[1]=address & 0xff; //last 8 bits
data[2]=rssi_i;

//memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

appDataReq.dstAddr = 0x401;
appDataReq.dstEndpoint = 2;
appDataReq.srcEndpoint = 2;
appDataReq.options = NWK_OPT_ENABLE_SECURITY;
appDataReq.data = data;                                                  // Toto mam na mysli
appDataReq.size = 3; //maybe more with Timestamp - will add later         // delka bude 512?
appDataReq.confirm = appDataConf;
NWK_DataReq(&appDataReq);

appUartBufferPtr = 0;
appDataReqBusy = true;
#ifdef USB_DEBUG
printf("Data sent to main anchor \n\r");
#endif
}
```

```C
BIGD v;

v = bdNew();

bdRandomSeeded(v, 508, (const unsigned char*)"", 0, my_rand);
	bdPrintHex("random=\n", v,"\n\r");
	/* NB bit length may be less than 508 */
printf("%u bits\n\r", bdBitLength(v));
  ```
