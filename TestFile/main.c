

#include <avr/io.h>
/*- Includes ---------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
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

/*- Includes OWN LIB -------------------------------------------------------------*/
#include "ECDH_functions.h"

/////USB//////////////
#include "USB_Stack/usb.h"

/*- Definitions ------------------------------------------------------------*/
#ifdef NWK_ENABLE_SECURITY
#define APP_BUFFER_SIZE     (NWK_MAX_PAYLOAD_SIZE - NWK_SECURITY_MIC_SIZE)
#else
#define APP_BUFFER_SIZE     NWK_MAX_PAYLOAD_SIZE
#endif

/*- Types ------------------------------------------------------------------*/
//typedef enum AppState_t
//{
//APP_STATE_INITIAL,
//APP_STATE_IDLE,
//APP_STATE_PosliC,
//APP_STATE_SLEEP,
//
//
//} AppState_t;

typedef enum {
	APP_STATE_LAUNCH,
	APP_STATE_WAIT,
	APP_STATE_NEXTSTEPACK,
	APP_STATE_WAITACK,
	APP_STATE_ACK,
	APP_STATE_IDLE,
} APP_STATES;

APP_STATES state;
//static AppState_t state = APP_STATE_INIT;

/*- Prototypes -------------------------------------------------------------*/




/*- Variables --------------------------------------------------------------*/
//static AppState_t appState = APP_STATE_INITIAL;

static NWK_DataReq_t napisneco;

static bool appDataReqBusy = false;

static SYS_Timer_t mujTimer;  // timer



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Variables
/////////////////////////////////////////////////////////////////////////////////////////////////////





//#ifdef USB_DEBUG
FILE usb_stream = FDEV_SETUP_STREAM(usb_putc_std, usb_getc_std,_FDEV_SETUP_RW);
//#endif

/*- Implementations --------------------------------------------------------*/

static void appDataConf(NWK_DataReq_t *req)
{
	appDataReqBusy = false;
	(void)req;
}


/*************************************************************************//**
*****************************************************************************/


// PAYLOADS
//*****************************************************************************/
static void appSendData(void)
{
	
	napisneco.dstAddr = 1-APP_ADDR;
	napisneco.dstEndpoint = APP_ENDPOINT;
	napisneco.srcEndpoint = APP_ENDPOINT;
	napisneco.options = NWK_OPT_ENABLE_SECURITY;  // encrypted
	napisneco.data = 65;
	napisneco.size = 1;
	napisneco.confirm = appDataConf;
	NWK_DataReq(&napisneco);
	
	printf("\n\rSend data");
}



/*************************************************************************//**
*****************************************************************************/

///////////////////////////
/// Timers

static void JardaTimerHandler(SYS_Timer_t *timer)
{
	appSendData();
	//(void)timer;
}



/*************************************************************************//**
*****************************************************************************/

// Receiver data

static bool ReceivePoint(NWK_DataInd_t *ind)
{

volatile uint16_t payload;

payload = ind->data;

printf("Cislo je %d\n\r", payload);


LED0SW;
return true;
}



/*************************************************************************//**
*****************************************************************************/
// NASTAVENI ADRESY, INDENTIFIKATORU
static void appInit(void)
{
	
// comunication	
NWK_SetAddr(APP_ADDR);
NWK_SetPanId(APP_PANID);
PHY_SetChannel(APP_CHANNEL);
#ifdef PHY_AT86RF212
PHY_SetBand(APP_BAND);
PHY_SetModulation(APP_MODULATION);
#endif
PHY_SetRxState(true);


// endpoint

NWK_OpenEndpoint(APP_ENDPOINT, ReceivePoint);

//HAL_BoardInit();
//BoardInit();


// Timers

mujTimer.interval = 1000;
mujTimer.mode = SYS_TIMER_PERIODIC_MODE;
mujTimer.handler =  JardaTimerHandler;



}

/*************************************************************************//**
*****************************************************************************/
///////////////////////////////////////////////////////////
// TASKHADLER FOR THE NODE A
///////////////////////////////////////////////////////////
static void APP_TaskHandler(void)
{

	appInit();
	
	SYS_TimerStart(&mujTimer);
	
	/////////////////////////////////////////////////
	// Application for pseudo-random selecting suitable input values
	int modulus, a_parameter, b_parameter; // -> pseudorandom, auto-selected inputs
	int X_first, Y_first, G_Order;  // -> Results for next proccess
	
	ObtainPointComplex(&modulus, &a_parameter, &b_parameter, &X_first, &Y_first, &G_Order);
	
	// --> encrypted modulus, a, b and send these values to NodeB
	
	
	/////////////////////////////////////////////////
	// Application for pseudo-random selecting a secret key
	int SecKey; // -> outputs
	SecretKey(&G_Order, &SecKey);   // G_Order -> in
	
	
	/////////////////////////////////////////////////
	// Application for compute public key (point)
	int containerP[2]; 
	/*
	container[0] = Xa;
	container[1] = Ya;
	*/
	PointComp(&X_first, &Y_first, &a_parameter, &modulus, &SecKey, containerP); //, int *STOPval);
	
	// --> send public key to NodeB
	// <-- get public key from Node B
	
	/////////////////////////////////////////////////
	// Application for compute a mutual point (get SecretKey)
	int Xa, Ya, Xb, Yb;
	int containerM[2];
	MutualPoint(&Xa, &Ya, &Xb, &Yb, &modulus, &a_parameter, containerM);
	
	/////////////////////////////////////////////////
	// Acknowledgement
	
	
}


///////////////////////////////////////////////////////////
// TASKHADLER FOR THE NODE B
///////////////////////////////////////////////////////////
static void APP_TaskHandlerB(void)  
{
	// <-- obtain decrypted modulus, a and b parameters
	
	/////////////////////////////////////////////////
	// Application for pseudo-random selecting a secret key
	int MOD, A, B, XFi, YFi, OrderG;
	
	TheFirstPoint(&MOD, &A, &B, &XFi, &YFI, &OrderG)
	
	/////////////////////////////////////////////////
	// Application for pseudo-random selecting a secret key
	int SecKey; // -> outputs
	SecretKey(&G_Order, &SecKey);   // G_Order -> in
	
	/////////////////////////////////////////////////
	// Application for compute public key (point)
	int containerP[2]; 
	/*
	container[0] = Xa;
	container[1] = Ya;
	*/
	PointComp(&X_first, &Y_first, &a_parameter, &modulus, &SecKey, containerP); //, int *STOPval);
	
	// --> send public key to NodeA
	// <-- get public key from NodeA
	
	/////////////////////////////////////////////////
	// Application for compute a mutual point (get SecretKey)
	int Xa, Ya, Xb, Yb;
	int containerM[2];
	MutualPoint(&Xa, &Ya, &Xb, &Yb, &modulus, &a_parameter, containerM);
	
	/////////////////////////////////////////////////
	// Acknowledgement
	
	
}

/*************************************************************************/
/*******************************************************************************/


/************************************************************************/
int main(void)
{

//#ifdef USB_DEBUG
usb_init();
/* redirect standard input/output (like printf()) to USB stream */

stdout = &usb_stream;
stdin  = &usb_stream;
//#endif



SYS_Init();while(1)
{
SYS_TaskHandler();
APP_TaskHandler();



}

}

// TEST ARTICLE

//void TEST(int *X, int *Y, int *mod, int *res){
	//
	//int x, y, modulus, result, mocnitel;
	//
	//x = *X;
	//y = *Y;
	//modulus = *mod;
	//mocnitel = 3;
		//
	//result = power(&x, &mocnitel);
	////result *= y;
	////result = modulo(&result, &modulus);
	//
	//*res = result;
	//
//}