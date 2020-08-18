# Historical Content of Consultations

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

# Konzultace 14.8.2020

Ke stazeni zde <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Stack%2014Aug.zip">zde </a> 

```C
#include <stdio.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

//PointCompBIGD(X, Y, a, mod, &iteration, &STOPval);
//int PointCompBIGD(BB X, BB Y, BB a_asymptote, BB modulus, uint32_t *iteration, int *STOPval)		


int PointCompBIGD(BB X, BB Y, BB a_asymptote, BB modulus, BB ResultX, BB ResultY, uint32_t *iteration, int *STOPval)
{
	
	BB Xi, Yi, Xj, Yj;
	BB mod, a, lambda;
	
	BB resultBigA, resultBigB, resultBigC;
	
	uint32_t repeat, result; 
	
	assert(X && Y && a_asymptote && modulus && ResultX && ResultY);

	
	Xi = bdNew();
	Yi = bdNew();
	Xj = bdNew();
	Yj = bdNew();
	
	mod = bdNew();
	a = bdNew();
	lambda = bdNew();	
	
		
	resultBigA = bdNew();	
	resultBigB = bdNew();
	resultBigC = bdNew();
	
	
	bdSetEqual(Xi, X);
	bdSetEqual(Yi, Y);
	
	bdSetEqual(Xj, Xi);
	bdSetEqual(Yj, Yi);

	
	bdSetEqual(a, a_asymptote);
	bdSetEqual(mod, modulus);
	
	
	// Value for number of iteration
	repeat = *iteration;	
	

	for(uint32_t i = 1; i <= repeat - 2; i++)
	{
		RecogniserBIGD(&result, Xi, Yi, Xj, Yj);
		
		printf("Napis  rozpoznan %d ", result);

		if(result == 1)
		{
			LamdaSameBIGD(resultBigA, mod, Xi, Yi, a);
			
			bdPrintDecimal("Lambda SAME = ", resultBigA, " \n\r");	
			
			XSameBIGD(resultBigB, mod, resultBigA, Xi);
			
			YUniBIGD(resultBigC, mod, resultBigA, Xi, Yi, resultBigB);
			
			
			*STOPval = 1;
			

		}

		else if(result == 2)
		{
			LamdaDiffBIGD(resultBigA, mod, Xi, Yi, Xj, Yj);
			
			bdPrintDecimal("Lmbda Diff = ", resultBigA, " \n\r");	

			
			XDiffBIGD(resultBigB, mod, resultBigA, Xi, Xj);
			
			YUniBIGD(resultBigC, mod, resultBigA, Xi, Yi, resultBigB);
			
			bdPrintDecimal("Xin", resultBigB, " \n\r");
			bdPrintDecimal("Yin", resultBigC, " \n\r");

			*STOPval = 1;
			

		}

		else if(result == 66)
		{
			
			*STOPval = 66;
		}
		
		
		
		bdSetEqual(Xj, resultBigB);	
		bdSetEqual(Yj, resultBigC);	

	}
	
	
	bdPrintDecimal("Xin", resultBigB, " \n\r");
	bdPrintDecimal("Yin", resultBigC, " \n\r");	


	bdSetEqual(ResultX, resultBigB);	
	bdSetEqual(ResultY, resultBigC);	
	
	
	bdFree(&Xi);
	bdFree(&Yi);
	bdFree(&Xj);
	bdFree(&Yj);
	
	bdFree(&mod);
	bdFree(&a);
	bdFree(&lambda);
	
}
```

# Konzultace 13.8.2020

Appka na odecitani, ktera resi problem zaporneho cisla. Pokud je vstup např. **360 - 5** provede se porovnani (**compare = bdCompare(a, b**), zda prvni hodnota je vetsi/mensi. Pokud je vetsi, probehne funkce na odecitani **bdSubstract(a, b);**, pokud je ovšem příklad **5 - 360**, provede se **bdSubstract(b, a);**.

Zaporné číslo zaniká v operaci **Modulo**. Zde v případě záporného vstupu je přidána další operace **bdSubstract**, která číslo invertuje (mod - vysledekMOD = konecny vysledek).

```C

#include <stdio.h>
#include <string.h>
#include <assert.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");

int TestM(){
	
	EMPTYLINE
	
	
	BB a, b, mod;
	BB resultA, resultB, resultC;
	
	int compare;
	
	
	a = bdNew();
	b = bdNew();
	mod = bdNew();
	
	
	resultA = bdNew();
	resultB = bdNew();
	resultC = bdNew();
	
	// 360 - 5 = 355
	//bdConvFromHex(a, "168");  // a = 360
	//bdConvFromHex(b, "5");    // b = 5
	
	
	// 5 - 360 = -355
	bdConvFromHex(a, "5");      // a = 5
	bdConvFromHex(b, "168");    // b = 360
	
	
	bdConvFromHex(mod, "22");  // mod  = 34
	
	compare = bdCompare(a, b);
	
	if(compare == 1){
		
		printf("Priklad 360 - 5 = 355\n\r");		
		bdSubtract(resultA, a, b);   // a - b = kladne cislo
		
		EMPTYLINE
		bdPrintDecimal("A je vetsi, vysledek a - b = ", resultA, " \n\r");
		
		bdModulo(resultB, resultA, mod);
		
		EMPTYLINE
		bdPrintDecimal("Zbytek po deleni kladneho cisla 355", resultB, " \n\r");
		
		
	}
	
	else if(compare == (-1)){
		
		printf("Priklad 5 - 350 = -355\n\r");	
		bdSubtract(resultA, b, a);   // b - a = kladne cislo
		
		EMPTYLINE
		bdPrintDecimal("B je vetsi, vysledek b - a  = ", resultA, " \n\r");
		
		
		bdModulo(resultB, resultA, mod);
		
		bdSubtract(resultC, mod, resultB);
		
		EMPTYLINE
		bdPrintDecimal("Zbytek po deleni zaporneho cisla - 355", resultC, " \n\r");	
		
	}
	
	
	bdFree(&a);
	bdFree(&b);
	bdFree(&mod);
	
	bdFree(&resultA);
	bdFree(&resultB);
	bdFree(&resultC);
	
	
}

```

# Konzultace 12.8.2020

Aplikace, ktera ze spoledneho bodu (treba X = 305, Y = 428) nasobenim spocita cislo vetsi nez je 2^127. Reseno pomoci cyklu while/do-while kde uvnitr cyklu je provaden soucin bodu tak dlouho, dokud neni vysledek vetsi ney 2^127 (128 bitove a vetsi cislo).

```C
#include <stdio.h>
#include <string.h>

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"
#define BB BIGD
#define EMPTYLINE printf("\n\r");



int TestK(){
	
	// prevod int na BIGD
	BIGD Xseed, Yseed, KeyPattern;
	BIGD resultA, resultB, num;
	
	uint8_t exponent = 127;
	int8_t comparsion;
	
	
	Xseed = bdNew();
	Yseed = bdNew();
	KeyPattern = bdNew();
	
	resultA = bdNew();
	resultB = bdNew();
	num = bdNew();

	int X = 305;            // Spolecny bod X
	int Y = 428;            // Spolecny bod Y
	
		
	bdSetShort(Xseed, X);
	bdSetShort(Yseed, Y);
		
	bdSetShort(num, 2);
	
	

	bdPower(KeyPattern, num, exponent);   // 2^128
	bdDecrement(resultA);
	
	
	
	
	bdPrintDecimal("Velikost klice ", KeyPattern, " \n\r");
	
	
	do{
	
		bdMultiply(resultB, Xseed, Yseed);

		comparsion = bdCompare(resultB, KeyPattern);
		
		
		 bdSetEqual(Xseed, resultB);
		 
		 bdMultiply(resultB, Xseed, Yseed);
		
		
	}while(comparsion != 1);
	
	
	
	
	
	bdPrintDecimal("Vypocitany klic", resultB, " \n\r");
	
	printf("Cislo proovnani %d", comparsion);
	
	
		
	return 0;
	
}
```


## Vlozeni klice do funkce NWK_SetSecurityKey

<p float="left">
  <img src="/Pictures (general)/SecurityA.PNG" width="1500" /> 
<p float="left"> </p>

```C
void NWK_SetSecurityKey(uint8_t *key)
{
  memcpy((uint8_t *)nwkIb.key, key, NWK_SECURITY_KEY_SIZE);
}
```

```C
#define NWK_SECURITY_KEY_SIZE        16
```


# Konzultace 11.8.2020

```C
/*
 * LWM_MSSY_deRF.c
 *
 * Created: 14.4.2017 12:56:52
 * Author : Ondra
 */ 

#include <avr/io.h>
/*- Includes ---------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "config.h"
#include "hal.h"
#include "phy.h"
#include "sys.h"
#include "nwk.h"
#include "sysTimer.h"
#include "halBoard.h"
#include "halUart.h"
//#include "mssy_endpoints.h"
//#include "mssy_requests.h"
#include "mssy_functions.h"
#include "util/delay.h"
#include "ADC_lib.h"
#include "main.h"
#include "sensors_interface.h"

/////USB//////////////
#include "USB_Stack/usb.h"

/////BIG N libs///////
#include "BigN/bigd.h"
#include "BigN/bigdRand.h"

#define EMPTYLINE printf("\n\r");

/*- Definitions ------------------------------------------------------------*/
#ifdef NWK_ENABLE_SECURITY
#define APP_BUFFER_SIZE     (NWK_MAX_PAYLOAD_SIZE - NWK_SECURITY_MIC_SIZE)
#else
#define APP_BUFFER_SIZE     NWK_MAX_PAYLOAD_SIZE
#endif

/*- Types ------------------------------------------------------------------*/
typedef enum AppState_t
{
	APP_STATE_FazeA,
	APP_STATE_FazeB,
	APP_STATE_FazeC,
} AppState_t;

/*- Prototypes -------------------------------------------------------------*/
static void appSendData(void);

//int TestB(void);

/*- Variables --------------------------------------------------------------*/
static AppState_t appState = APP_STATE_FazeA;    // Prvotni faze

static SYS_Timer_t appTimerA;
static SYS_Timer_t appTimerB;

static NWK_DataReq_t appDataReq;
static bool appDataReqBusy = false;


// USB printf
FILE usb_stream = FDEV_SETUP_STREAM(usb_putc_std, usb_getc_std,_FDEV_SETUP_RW);


/*- Implementations --------------------------------------------------------*/

/*************************************************************************//**
*****************************************************************************/
static void appDataConf(NWK_DataReq_t *req)
{
appDataReqBusy = false;
(void)req;
}

/*************************************************************************//**
*****************************************************************************/
static void SendDataA(void)
{
	if (appDataReqBusy || 0 == appUartBufferPtr)
	return;

	memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

	appDataReq.dstAddr = 0xFFFF;
	appDataReq.dstEndpoint = APP_ENDPOINT;
	appDataReq.srcEndpoint = APP_ENDPOINT;
	//appDataReq.options = NWK_OPT_ENABLE_SECURITY;
	appDataReq.data = 65;
	appDataReq.size = 1;
	appDataReq.confirm = appDataConf;
	NWK_DataReq(&appDataReq);

	appUartBufferPtr = 0;
	appDataReqBusy = true;
	
	
	// Posilam data data
	printf("Odeslana data: ", appDataReq.data);
	
}


/*************************************************************************//**
*****************************************************************************/
static void SendDataA_TimerHandler(SYS_Timer_t *timer)
{
	SendDataA();
	//(void)timer;  // proc??
}


/*************************************************************************//**
*****************************************************************************/

static bool DostavamData(NWK_DataInd_t *ind)
{

	volatile uint16_t ObtainData;

	ObtainData= ind->data;
	
	
	// Tisk obdrzenych hodnot
	printf("Obdrzena data %D \r\n", ObtainData);
	
	}



/*************************************************************************//**
*****************************************************************************/
static void appInit(void)
{
NWK_SetAddr(APP_ADDR);
NWK_SetPanId(APP_PANID);
PHY_SetChannel(APP_CHANNEL);
#ifdef PHY_AT86RF212
PHY_SetBand(APP_BAND);
PHY_SetModulation(APP_MODULATION);
#endif
PHY_SetRxState(true);

NWK_OpenEndpoint(1, DostavamData);              // Endpoint
NWK_OpenEndpoint(2, DostavamData);              // Endpoint

//NWK_OpenEndpoint(APP_ENDPOINT, DostavamData);   // Endpoint


//NWK_OpenEndpoint(APP_ENDPOINT, appDataInd);

HAL_BoardInit();

appTimerA.interval = 1000;
//appTimerA.mode = SYS_TIMER_INTERVAL_MODE;
appTimerA.mode = SYS_TIMER_PERIODIC_MODE;
appTimerA.handler = SendDataA_TimerHandler;


}

/*************************************************************************//**
*****************************************************************************/
static void APP_TaskHandler(void)
{
switch (appState)
{
case APP_STATE_FazeA:
{
appInit();

SYS_TimerStart(&appTimerA);

} break;

default:
break;
}
}


/*************************************************************************/
int main(void)
{
	usb_init();
   /* redirect standard input/output (like printf()) to USB stream */
	stdout = &usb_stream;
	stdin  = &usb_stream;
	LED1ON;
	printf("Hello :-) \n\r");
	
	
	EMPTYLINE


	while(1)
	{
		SYS_TaskHandler();
		APP_TaskHandler();
		
	}
}

```

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
	
	// Prevod na oktety
	delka = bdConvToOctets(a, NULL, 0);
	array = malloc(delka);
	bdConvToOctets(a, array, delka);
	
	// Prevod na oktety
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

## Data z payloadu

```C
static bool appAnchorData(NWK_DataInd_t *ind)
{

uint16_t address = ind->srcAddr;
volatile uint16_t NodeAddress;
volatile uint16_t NodeAddressa;
volatile uint16_t NodeAddressb;
NodeAddressa= ind->data[0]<<8;
NodeAddressb= ind->data[1];

NodeAddress= NodeAddressa + NodeAddressb;

int8_t rssiX=ind->data[2];
#ifdef USB_DEBUG
printf("We got data from anchor %d: Node: %d, RSSI: %d\n\r", address,NodeAddress,rssiX);
#endif

LED0SW;
//other lines
matrix[address-0x401][NodeAddress-1] = rssiX;
return true;

}
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

# Konzultace 6.8.2020

<p float="left">
  <img src="/Pictures (general)/FlowCH Phase A.png" width="300" /> 
<p float="left"> </p>

## Rand funkce

<p float="left">
  <img src="/Pictures (general)/RandPic.PNG" width="400" /> 
<p float="left"> </p> 

```C
BIGD  a, n;
	
	a = bdNew();
	n = bdNew();
	
	bdSetShort(n, 25);
	
	size_t bdRandomNumber (a, n);
	
	bdPrintHex("RAND HEX je 0x ", a, "\n\r");
	bdPrintDecimal("RAND DEC je ", a, "\n\r");
	
	bdFree(&a);
	bdFree(&n);
```

## Fermat
```C

BIGD TESTNUM, vysledek;
	
	TESTNUM = bdNew();
	vysledek = bdNew();
	
	bdSetShort(TESTNUM, 17);
	//bdConvFromHex(TESTNUM, "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000004b");
	
	//printf("testovaci cislo je %d\n\r", TESTNUM);
	bdPrintDecimal("testovaci cislo je ", TESTNUM, "\n\r");


	bdSetShort(vysledek, fermat_test(TESTNUM));
	
	bdPrintDecimal("Vysledek Fermat testu ", vysledek, "\n\r");
		
	
	bdFree(&TESTNUM);
	bdFree(&vysledek);	
```

## bdPower
<p float="left">
  <img src="/Pictures (general)/dbPower.PNG" width="400" /> 
<p float="left"> </p> 

```C
BIGD CisloA, CisloB, CisloC;
		
		CisloA = bdNew();
		CisloB = bdNew();
		CisloC = bdNew();		
		
			
		bdSetShort(CisloB, 25);
		bdSetShort(CisloC, 5);
		
		//bdPower(CisloA, CisloB, CisloC);          //  y = g^n (up to available memory!) 
		bdMultiply(CisloA, CisloB, CisloC);     //  w = u * v. 
		
		bdPrintHex("Test Modulo HEX je 0x ", CisloA, "\n\r");
		bdPrintDecimal("Test Modulo DEC je ", CisloA, "\n\r");
		
		
		bdFree(&CisloA);
		bdFree(&CisloB);
		bdFree(&CisloC);	
```

## Původní kód
```C
// int TheFirstPoint(BIGD MOD, BIGD A, BIGD B, BIGD Xfirst, BIGD Yfirst, BIGD OrderG)
void TheFirstPoint(int *MOD, int *A, int *B, int *Xfirst, int *Yfirst, int *OrderG)
{  
        // Jak zmeni toto pole?
	int modulus, a, b;
	int poleA[1000];
	int poleB[1000];

	modulus = *MOD;
	a = *A;
	b = *B;

	// Application XPart
	YPart (&modulus, poleA);
	
	// Application YPart
	XPart(&modulus, &a, &b, poleB);

	// Iterations
	int X_iter = modulus - 1;
	int Y_iter = ((modulus - 1) / 2) + 1;
	
	// Computing order
	int order = 0;
	
	#ifdef PRINT_ON
	// Point64_ts
	int x, y, y_neg;
	#endif // PRINT_ON

	for(int k = 0; k <= X_iter; k++)  // Give X's
	{
		for(int i = 0; i <= Y_iter; i++)  // Give Y's
		{
			if (poleA[i] == poleB[k])
			{
				if(order == 0)
				{

					*Xfirst = k;
					*Yfirst = i;
				}
				
				#ifdef PRINT_ON
				x = k;
				y = i;
				y_neg = modulus - i;
				
				
				printf("Yes, this number is in array\n\r");
				printf("Jedna se o cisla %d a %d\n\r", poleA[i], poleB[k]);
				EMPTYLINE
				printf("Coordinates are [%4d,%4d] [%4d,%4d] \n\r", x, y, x, y_neg);
				#endif // PRINT_ON

				order++;

			}
		}

	}

	order *= 2;
	order += 1;

	*OrderG = order;
}
```

```C
void checkValAB(int64_t *mod, int64_t *A, int64_t *B, int64_t *TESTvalue)
{
	int64_t a, b, compute, mocnitelA, mocnitelB, MOD;

	MOD = *mod;
	a = *A;
	b = *B;

	if(a == MOD)
	{

		*TESTvalue = 2;
	}

	else if(b == MOD)
	{

		*TESTvalue = 2;
	}

	else
	{
		mocnitelA = 3;
		mocnitelB = 2;

		compute =  4 * (power(&a, &mocnitelA)) + 27 * (power(&b, &mocnitelB));
		compute = modulo(&a, &MOD);
		
		if (compute > 0)
		{
			*TESTvalue = 1;
			
		}
		else
		{
			*TESTvalue = 2;
		}
		

	}
}
```

# Konzultace 5.8.2020

## bdModSquare (bigd.c)
```C
	 //int bdModSquare(BIGD a, BIGD x, BIGD m)
	 //Computes a = x^2 mod m
	 
	 int NumA, NumB, NumC;
	 
	 NumB = 36;
	 NumC = 5;
	 
	 bdModSquare(NumA, NumB, NumC);
	 
	 printf("Vysledek je %d", NumA);
```

```C
/** Computes a = x^2 mod m */
int bdModSquare(BIGD a, BIGD x, BIGD m)
{
	size_t n;
	int status;

	assert(a && x && m);
	/* Make sure all variables are the same size */
	n = max(x->ndigits, m->ndigits);

	bd_resize(a, n);
	bd_resize(x, n);
	bd_resize(m, n);

	/* Do the business */
	status = mpModSquare(a->digits, x->digits, m->digits, n);

	a->ndigits = mpSizeof(a->digits, n);

	return status;
}
```

## Test prvočísla
```C
	int TESTNUM = 2;
	printf("testovaci cislo je %d\n\r", TESTNUM);
	for(int iss = 0; iss < 10; iss++){
	int vysledek = fermat_test(&TESTNUM);
	printf("Vysledek testu je %d\n\r", vysledek);
	}
```

<p float="left">
  <img src="/Pictures (general)/Putty0508.PNG" width="800" /> 
<p float="left"> </p> 


## Test flashnutí desek
U jedné desky blikají ledky pomaleji. I přesto, že jsem paměti pročistil (Erase) a nahrál stejný program na obě desky. **Může to ovlivnit nějak běh aplikace?**

```C
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRE |= (1<<PE3);   // operace bitovy OR  |=
	DDRE |= (1<<PE4);   // operace bitovy OR  |=
	DDRG |= (1<<PG5);   // operace bitovy OR  |=
	
	

	while (1)
	{
		PORTG |= (1<<PG5);
		_delay_ms(100);
		
		PORTE |= (1<<PB3);       // operace bitovy OR  |=
		_delay_ms(100);

		
		PORTE |= (1<<PB4);
		_delay_ms(100);
		
			
		PORTG &= ~(1<<PG5);
		_delay_ms(100);
		
		PORTE &= ~(1<<PB3);     // operace bitovy AND  &=  ~ negace jednicky
		_delay_ms(100);
		
		PORTE &= ~(1<<PB4);
		_delay_ms(100);
		
	}
}

```

# Konzultace 3.7.2020

Pokus o kompilaci BigN ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/BigN%20lib.zip">zde</a>. </a>  </p>

<p float="left">
  <img src="/Pictures (general)/Errata.PNG" width="800" /> 
<p float="left"> </p> 


### Alg. pro spojovani bitů
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTYLINE printf("\n");

int main()
{

    srand((unsigned int) time(NULL));

    int Array[513];

    int round = 4;
    int BitLen;
    char buffer [513];


    printf("Enter Bit Lenght (1 = 1111):\n");
    scanf("%d", &BitLen);
    EMPTYLINE


    BitLen -= 1;


    Array[0] = 15;                   // Testovaci hodnota 15 MAX
//    Array[0] = rand() % 16;

    itoa (Array[0],buffer,2);

    printf("Round: 2^%d\n", round);
    printf("DEC rand: %d\n", Array[0]);
    printf("BIN rand: %s\n", buffer);
    EMPTYLINE
    for(int j = 1; j <= BitLen; j++)
    {

        Array[j] = Array[(j-1)] + (15 << round);                   // Testovaci hodnota 15 MAX
//        Array[j] = Array[(j-1)] + ((rand() % 16) << round);

        itoa (Array[j],buffer,2);


        round += 4;

        printf("Round: 2^%d\n", round);
        printf("DEC rand: %d\n", Array[j]);
        printf("BIN rand: %s\n", buffer);
        EMPTYLINE


    }



    EMPTYLINE
    printf("TOTAL DEC: %d\n", Array[BitLen]);
    itoa (Array[BitLen],buffer,2);
    printf ("TOTAL BIN: %s\n",buffer);

    return 0;
}
```

<p float="left">
  <img src="/Pictures (general)/OknoBits.PNG" width="800" /> 
<p float="left"> </p> 


### Ukazatel může být v jazyce C přetypován na specifický typ
```C
#include <stdio.h>
#include <stdlib.h>

int main()
{

//    int * pole = malloc(10 * sizeof(int));            // bez přetypování v jazyce C
    int * pole = (int *) malloc(10 * sizeof(int));      // s přetypování v jazyce C

    pole[0] = 12;
    pole[1] = 5;
    pole[2] = 2;

    for(int i = 0; i < 3; i++)
    {

        printf("Cislo je %d\n", pole[i]);
    }

    free(pole);  

    return 0;
}
```
### Maxima

**4 bit**  => 0-15   1111 (4x) </br>
**8 bit**  => 0-255  1111 1111 (8x) </br>
**16 bit** => 0-65535  1111 1111 1111 1111 (16x)  </br>
**32 bit** => 0-4294967295 1111 1111 1111 1111 1111 1111 1111 1111 (32x) </br>

### Velikosti jednolivých typů

<p float="left">
  <img src="/Pictures (general)/Typerange.PNG" width="800" /> 
<p float="left"> </p> 

### Funkce <stlib.h>
**calloc** - alokace dynamické paměti pro pole objektů </br>
**malloc** - alokace bloku dynamické paměti </br>
**realloc** - změna velikosti bloku dynamické paměti </br>
**free** - uvolnění dynamické paměti </br>
**sizeof** - velikost datoveho typu </br>



# Konzultace 27.7.2020

Jedná se u ukázkový prototyp algoritmu, kde jednotlivé iterace jsou vytvořeny přímo v kódu (namísto **for cyklu**). Tento kód pseudonáhodně generuje 2^12 číslo, které je složeno ze tří 2^4 čísel (viz obrázek níže). Výstup je zobrazen na obrázku pod kódem.

<p float="left">
  <img src="/Pictures (general)/MyThinkAdvance.PNG" width="800" /> 
<p float="left"> </p> 


**Otázka: Je tato myšlenka správná? Lze takto navýšením počtu iterací na 128, tj. 2^(4·128) => 2^(512) dosáhnout čísla o velikosti 512 bitů?**

Na zaslaný link jsem díval, zatím jsem jej nezkoušel kompilovat.

```c
#include <stdio.h>
#include <stdlib.h>
#define EMPTYLINE printf("\n");


int main()
{

    srand((unsigned int) time(NULL));

    int RandNUM;
    int resA, resB, resC, TOTAL;
    int num;
    char buffer [4];
    char bufferTOTAL [4];



    num = 0;

    printf("Davka %d\n", num);
    RandNUM = rand()%16;
    printf("Rand DEC %d\n", RandNUM);
    itoa (RandNUM,buffer,2);
    printf ("Rand BIN: %s\n",buffer);
    resA = RandNUM << num;


    EMPTYLINE

    num = 4;

    printf("Davka %d\n", num);
    RandNUM = rand()%16;
    printf("Rand DEC %d\n", RandNUM);
    itoa (RandNUM,buffer,2);
    printf ("Rand BIN: %s\n",buffer);
    resB = RandNUM << num;

    EMPTYLINE

    num = 8;

    printf("Davka %d\n", num);
    RandNUM = rand()%16;
    printf("Rand DEC %d\n", RandNUM);
    itoa (RandNUM,buffer,2);
    printf ("Rand BIN: %s\n",buffer);
    resC = RandNUM << num;


    EMPTYLINE

    TOTAL = resA + resB + resC;

    printf("TOTAL DEC %d\n", TOTAL);
    itoa (TOTAL,buffer,2);
    printf ("TOTAL BIN %s\n",buffer);

}

```

<p float="left">
  <img src="/Pictures (general)/CommandLine.PNG" width="800" /> 
<p float="left"> </p> 

# Konzultace 23.7.2020
## Test prvočíselnosti

### Utility function to do modular exponentiation (x^y) % p 
```C
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int x, y, p;
    x = 174;
    y = 110;
    p = 221;


    int result = power(x, y, p);

    printf("%d", result);

}


int power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

```


# Konzultace 20.7.2020

## Fáze generování 32 bitového čísla - dosazeni vetsiho cisla nez nabizi rand()

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int randNUM, SUM;

    srand((unsigned int) time(NULL));

    for(int i = 0; i < 128; i ++){

            randNUM = (rand()*rand()*rand());           // dosazeni vetsiho cisla
            printf("%d\n\r", randNUM);

            SUM += randNUM;
    }

    printf("%d\n\r",SUM);


    return 0;
}
```

## Násobení pomocí bitových operací
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j, i;

    j = 80;

    i = (j << 6) + (j << 4);    // vysledek je 6400

    printf("Cislo je %d", i);

    return 0;
}
```

## Spojení jednotlivých 32bit stringu do 512 stringu - metodika
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    int length;


    char pp [] = "57";
    char pq [] = "348";

    strcat(pp, pq);

    printf("%s\n", pq);

    length = strlen(pp);

    printf("Result is %d", length);


    return 0;
}
```

## Metodika spojovani (jde to  jinak než pomocí for?)
```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY_LINE printf("\n");

int main()
{


    uint8_t randNUM, SUM;
    char buffer[10];
    char BigN[] = "0";

    srand((unsigned int) time(NULL));

    for(int i = 0; i < 8; i ++)                // 8 X 4 bit cislo = 32 bitove cislo
    {

        SUM = rand() % 16;                     // pseudorandomni cislo o 4 bitove delce
        printf("DEC = %d\n\r",SUM);            // ukazka pseudorandomniho cisla o 4 bitove delce

        itoa(SUM,buffer,2);                    // prevedeni do binarni soustavy

        printf("BIN = %s\n", buffer);          // ukazka cisla jako stringu

        strcat(BigN, buffer);                  // spojeni aktualniho vysledku s predchozim - postupne nabalovani

        EMPTY_LINE


    }

    printf("TOTAL = %s\n", BigN);             // vypis 32 bitoveho cisla


    return 0;
}
```

# Konzultace 24.6.2020

* jak spolehlivě změřit délku čísla
* jak vygenerovat číslo o délce 512 bitů
* problematika velkých čísel obecně


Doplnění znalostí slédnutím <a href="https://www.udemy.com/course/advanced-c-programming-course/">kódu</a> online kurzu. </a>  </p>


* **Storage classes**</p>
auto, register, static and extern

* **Advanced datay types**</p>
- typedef, varibale length arrays, flexible array numbers, complex number types

* **Type qualifiers**</p>
- const, volatile, and restrict

* **Bit manipulation** </p>
binary number and bits
binary operators (logical and shifting)
bitmask and bitfields

## Nedostatky ve výměně klíčů

<p float="left">
  <img src="/Pictures (general)/PostApplication/1.png" width="800" /> 
<p float="left"> </p> 

## Metoda "hrubou silou"

<p float="left">
  <img src="/Pictures (general)/PostApplication/Post Prime.png" width="800" /> 
<p float="left"> </p> 

## Metoda "hrubou silou"

<p float="left">
  <img src="/Pictures (general)/PostApplication/Post Sec.png" width="800" /> 
<p float="left"> </p> 


# Konzultace 22.6.2020

* Prezentace zredukována na 20 slidů (včetně úvodu a konce) </p>
* Některé slidy jsou jako jen úvodní pro orientaci co je prezentováno </p>
* otázky oponenta přemístěny za konec </p>
* nejsem si jist s odpovědima, hlavně na první a poslední </p>
* Poslední otázku jsem dal 25vteřin, tak dlouho trvá otestování čísla níže, který by mělo být délky 512b. Ale test jsem provedl na ATmega328P (Arduino), dle toho <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/PrimeNum.md">kódu</a> (upravená samostatná aplikace použitá ve Stacku). </a>  </p>



356417084928445152684699010152547539451415158798870606897312878771007950907120307985160213430195101707592616586985175716804924430139137110166651344489516545583806446798673526912701909245186841084227573610707303357554822894457033401888346712768146099942517442956191287929228634202168957991987375587974608403841449353343497402957815179207532995702874118295734527260619948972153130850121651797902296255767101937512405820060180893245274478095354635219463460997962771908318906965679929530416325228343067051225214865767389848921242643394571823819598343870342601113781409x43781042013591267880049995719459462645581589111630238290276612999914991082941727325622500390644167316585711234259747167611065659833573328522233579148437709047378845925963164627093062099422280225064498226327224675104082213816289771633154407100952732491802803493003388805811229004430586052154844745418148902927372815455723249635521278876725300114591030266399848574558089274177686846678088638590609914845668407364346180405137133885107847792670912948133923890228693622120270113338811375943240333174841485735633021627509224891749394218645582652974283417108993


<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/22.png" width="800" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/23.png" width="800" /> 
<p float="left"> </p> 



## Ukázka prezentace v .pdf

Prezentace ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Presentation%202.0.pdf">zde</a>. </a>


# Prezentace

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/01.png" width="700" /> 
<p float="left"> </p> 

**Zde jen prezentace myšlenky rozčlenění výměny na tři fáze.**

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/02.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/03.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/04.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/05.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/06.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/07.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/08.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/09.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/10.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/11.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/12.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/13.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/14.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/15.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/16.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/17.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/18.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/19.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/20.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/21.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/22.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver2.00 FRAME/23.png" width="700" /> 
<p float="left"> </p> 



# Konzultace 19.6.2020

## Ukázka prezentace

Prezentace ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis%20presentation%202020.pdf">zde</a>. </a>

* Prezentace obsahuje obsahuje toho záměrně více, než se do 10 min vejde </p>
* Byla zde snaha maximálně využít vytvořených vývojových diagramů </p>
* Prosím o radu, co vyřadit a kde přidat více podrobností </p>
* Prezentace je logicky členěná dle toho, jak jednotlivé fáze přicházejí na řadu. </p>
* První část prezentace je zaměřena na vysvětlení algoritmu výměny (bez komunikace mezi deskami). </p>
* Druhá část je věnována impmentaci v rámci LWM. </p>
* Je zde pomocí vývojových digramu popsáno fungování **TaskHandleru** a přepínání mezi jednotlivýmy případy **case** </p>

# Prezentace

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/01.png" width="700" /> 
<p float="left"> </p> 

### Cíle práce
Tunto slide se mi zdá přebytečný. Komise bude určitě vědět, co je tématem.
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/02.png" width="700" /> 
<p float="left"> </p> 

### Obecné schéma výměny klíčů
Zde bych jen řekl, že výměnu klíčů je realizována ve třech fázích a je založena na eliptických křivkách. A hnedka přepnul na další slide.
</p>
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/03.png" width="700" /> 
<p float="left"> </p> 

### Fáze A (slide 4 - 18)
Zde bude postupně popsána Fáze A, včetně komponent. Tuto část bych ovšem zestručnil. K podprogramům **TheFirstPoint**, **PointComp**, **VerifyOfPoint** bych věnoval jen jeden slide s popisem (ačkoliv aplikace  **TheFirstPoint** je pro ukázku popsána detailně), co ta funkce umí a dál bych to nerozebíral. Ačkoliv to může být zajímavé, spotřebujeto nějaký čas, který bude chybět jinde. Na **slidu 18** je ukázka, jak pracuje fáze A, tj. výpočet grupy bodů na jednoduchém příkladu. Ten bych tam nechal. Je to důkaz, že ta spleť kódů funguje a generuje nějaké hodnoty.

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/04.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/05.png" width="700" /> 
<p float="left"> </p> 


<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/06.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/07.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/08.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/09.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/10.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/11.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/12.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/13.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/14.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/15.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/16.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/17.png" width="700" /> 
<p float="left"> </p> 


<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/18.png" width="700" /> 
<p float="left"> </p> 


### Fáze B (slide 19 - 21)
Úvodní stránka Fáze B, ke které řeknu, že má za úkol volbu tajného klíče a výpočet sdíleného klíče. Pro odesilatele a příjemce se liší, protože příjemce si musí z obdržených hodnot *p*, *a* a *b* spočítat generátor a řád. V dalším **20** slidu bych jen řekl, že aplikace je vytvořena jako samostatný blok, který umožňuje snadnou implementaci do algoritmu. Ke slidu **21** bych jen dodal, že aplikace je osahuje funkci (nebo spíše vnořenou aplikaci), která pseudonáhodně vybírá tajný klíč a je zde ošetření proti nulovému výsledku.
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/19.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/20.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/21.png" width="700" /> 
<p float="left"> </p> 

### Fáze C (slide 22 - 24)
Opět prezentace dle schématu Fáze B. Říct jen, že tato fáze slouží k výpočtu společného bodů. Obsahuje podaplikakci (další slide), která rozpozná z obdrženého bodu od protistrany její tajný klíč (na základě znalosti pořadí v grupě).
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/22.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/23.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/24.png" width="700" /> 
<p float="left"> </p> 

### Implementace do LWM stacku (slide 25 - 28)
Tady jsem umístil vývojové diagramy, které popisují zapínání jednotlivých fází ve stacku a odesílání dat.

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/25.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/26.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/27.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/28.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Questions.png" width="700" /> 
<p float="left"> </p> 


<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/29.png" width="700" /> 
<p float="left"> </p> 


# Konzultace 8.6.2020

## Text práce

PDF práce k nahledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis%20862020.pdf">zde</a>. </a>

Souhrn všech spuštěcích bloků, <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Summary%20of%20ECDH%20app.md">zde</a>. </a>

Stack ke stažení v ZIP, <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Protocol%20Stack%20v2020%2086.zip">zde</a>. </a>

## Securitty
```c
void NWK_SetSecurityKey(uint8_t *key)
{
  memcpy((uint8_t *)nwkIb.key, key, NWK_SECURITY_KEY_SIZE);
}


```
## Vzor TaskHandleru
```c

Otevřít tento HTML dokument v novém okně
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


## App_task Handler
```c
case APP_STATE_SEND_PARAMTERES:
{
	// send array [2] p, a, b
	SYS_TimerStart(&DataSendTimer);
	
	state = APP_STATE_GOTO_PHASE_B;
	break;
	}
	
case APP_STATE_GOTO_PHASE_B:
{
	
	ECDH_PHASE_BA(&Order, &X_first, &Y_first, &a_parameter, &mod, containerB);
	
	if(containerB[0] > 0 && containerB[1] >0){
		state = APP_STATE_SEND_COMMON_POINT,;
	}
	
}


// Incializace C
//state = APP_STATE_GOTO_PHASE_C;
//break;

case APP_STATE_SEND_COMMON_POINT,:
{
	// send array [1] X, Y
	SYS_TimerStart(&DataSendTimer);
	break;
}

	// Incializace C
	//state = APP_STATE_GOTO_PHASE_C;
	//break;



case APP_STATE_GOTO_PHASE_C:
{

	ECDH_PHASE_C(&MSKey, &X_first;, &Y_first;, &X_obtain, &Y_obtain, &mod, &a_parameter, &Order, &MutKEY, containerC);
	

	break;
}

default:
break;
}
}

## Arch se všemi flowcharty (pro Key Exchange)

<p float="left">
  <img src="/Pictures (general)/SuperAll.png" width="800" /> 
<p float="left"> </p> 
```


# Konzultace 4.6.2020

## Text práce

PDF práce k nahledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis%204_6_2020.pdf">zde</a>. </a>

## Aplikace ECDH

<p float="left">
  <img src="/Pictures (general)/GeneralFlowchart.png" width="800" /> 
<p float="left"> </p> 

Pro přetypování na typ **int64_t** funguje i s velkými čísly. Přpravena na implentaci do stacku. Zbývá jen sjednotit některé drobné odchylky ve společných proměnných, které budou obsaženy v **main.c**. Imho, tímto je aplikace na výměnu klíče hotova.

Je seskupena do čtyř bloků pro všechny tři fáze výměny klíče:

* výběr vstupních hodnot -> **Phase I**
* Generování tajného klíče a výpočet bodu pro sdílení s protistranou -> **Phase II A** a **Phase II B**
* Výpočet společného klíče a bodu -> **Phase III**

**Otázka:** Zítra bych na kozultaci pořešil, jak sprvně vytvořit vhodný klíč z bodu, který je výstupem z bloku **PHASE 3**. Mohl bych použít svoji padding aplikaci nebo nějakou metodu součtu (dle Vaší rady). To se poradíme na konzultaci.

### PHASE 1

**Input:** the application chooses the values by itself  </p>
**Output:** modulus, a parameter, b parameter, XFirst, YFirst, GOrder </p>

```c
// PROTOTYPE
void ECDH_PHASE_A();
```
```c
int64_t mod, a_parameter, b_parameter, X_first, Y_first, G_Order;

ECDH_PHASE_A(&mod, &a_parameter, &b_parameter, &X_first, &Y_first, &G_Order);
```

### PHASE 2 A

**Input:** Order, XFirst, YFirst, a parameter, modulus </p>
**Output:** coordinates of Point for sharing, MySecretKey *(all values are stored in array)* </p>

```c
// PROTOTYPE
void ECDH_PHASE_BA();
```
```c
int64_t Order, Xf, Yf, a, mod;
int64_t container[3];

ECDH_PHASE_BA(&Order, &Xf, &Yf, &a, &mod, container);
```

### PHASE 2 B

**Input:** modulus, a parameter, a parameter </p>
**Output:** coordinates of Point for sharing, MySecretKey *(all values are stored in array)* </p>

```C
// PROTOTYPE
void ECDH_PHASE_BB();
```
```C
int64_t mod, a, b;
int64_t container[3];

ECDH_PHASE_BB(&mod, &a, &b, container);
```

### PHASE 3

**Input:** MySecretKey, XFirst, YFirst, modulus, a parameter, order </p>
**Output:**  MutualKey, MutualPoint *(in array)* </p>

```c
// PROTOTYPE
void ECDH_PHASE_C();
```
```c
int64_t MSKey, XF, YF, XO, YO, mod, a, order, MutKEY;
int64_t container[2];

void ECDH_PHASE_C(&MSKey, &XF, &YF, &XO, &YO, &mod, &a, &order, &MutKEY, container);
```

-----------------------------------------------------------------------------------------------------------------

## Padding APP

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/padding.PNG" width="300" /> 
<p float="left"> </p> 
* *Zatatím nepřetypováno a netestováno na uin64_t*

```c

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

# Konzultace 4.6.2020

## Text práce

PDF práce k nahledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis%204_6_2020.pdf">zde</a>. </a>

## Aplikace ECDH

<p float="left">
  <img src="/Pictures (general)/GeneralFlowchart.png" width="800" /> 
<p float="left"> </p> 

Pro přetypování na typ **int64_t** funguje i s velkými čísly. Přpravena na implentaci do stacku. Zbývá jen sjednotit některé drobné odchylky ve společných proměnných, které budou obsaženy v **main.c**. Imho, tímto je aplikace na výměnu klíče hotova.

Je seskupena do čtyř bloků pro všechny tři fáze výměny klíče:

* výběr vstupních hodnot -> **Phase I**
* Generování tajného klíče a výpočet bodu pro sdílení s protistranou -> **Phase II A** a **Phase II B**
* Výpočet společného klíče a bodu -> **Phase III**

**Otázka:** Zítra bych na kozultaci pořešil, jak sprvně vytvořit vhodný klíč z bodu, který je výstupem z bloku **PHASE 3**. Mohl bych použít svoji padding aplikaci nebo nějakou metodu součtu (dle Vaší rady). To se poradíme na konzultaci.

### PHASE 1

**Input:** the application chooses the values by itself  </p>
**Output:** modulus, a parameter, b parameter, XFirst, YFirst, GOrder </p>

```c
// PROTOTYPE
void ECDH_PHASE_A();
```
```c
int64_t mod, a_parameter, b_parameter, X_first, Y_first, G_Order;

ECDH_PHASE_A(&mod, &a_parameter, &b_parameter, &X_first, &Y_first, &G_Order);
```

### PHASE 2 A

**Input:** Order, XFirst, YFirst, a parameter, modulus </p>
**Output:** coordinates of Point for sharing, MySecretKey *(all values are stored in array)* </p>

```c
// PROTOTYPE
void ECDH_PHASE_BA();
```
```c
int64_t Order, Xf, Yf, a, mod;
int64_t container[3];

ECDH_PHASE_BA(&Order, &Xf, &Yf, &a, &mod, container);
```

### PHASE 2 B

**Input:** modulus, a parameter, a parameter </p>
**Output:** coordinates of Point for sharing, MySecretKey *(all values are stored in array)* </p>

```C
// PROTOTYPE
void ECDH_PHASE_BB();
```
```C
int64_t mod, a, b;
int64_t container[3];

ECDH_PHASE_BB(&mod, &a, &b, container);
```

### PHASE 3

**Input:** MySecretKey, XFirst, YFirst, modulus, a parameter, order </p>
**Output:**  MutualKey, MutualPoint *(in array)* </p>

```c
// PROTOTYPE
void ECDH_PHASE_C();
```
```c
int64_t MSKey, XF, YF, XO, YO, mod, a, order, MutKEY;
int64_t container[2];

void ECDH_PHASE_C(&MSKey, &XF, &YF, &XO, &YO, &mod, &a, &order, &MutKEY, container);
```

-----------------------------------------------------------------------------------------------------------------

## Padding APP

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/padding.PNG" width="300" /> 
<p float="left"> </p> 
* *Zatatím nepřetypováno a netestováno na uin64_t*

```c

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
=====================================================================================================================================

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
  
  
  
  
  
  
