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
