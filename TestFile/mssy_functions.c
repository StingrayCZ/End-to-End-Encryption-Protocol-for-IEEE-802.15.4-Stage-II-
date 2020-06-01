/*
 * mssy_functions.c
 *
 * Created: 6.4.2017 16:13:19
 *  Author: Krajsa
 */ 
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
#include "mssy_endpoints.h"
#include "mssy_requests.h"
#include "mssy_functions.h"
#include "main.h"
#include "sensors_interface.h"
#include "ADC_lib.h"

//#include "astudio/buffer.h"


void BoardInit(){
	#ifdef HAL_ATMEGA128RFA1
	sbi(DDRG,LED0); //led vystup
	sbi(DDRE,LED1);
	sbi(DDRE,LED2);
	ADC_Init(4,2);
	TWI_MasterInit();
	BMA150_Init();
	ISL29020_Init();
	TMP102_Init();
	#endif
	#ifdef HAL_ATMEGA256RFR2
	sbi(DDRB,LED1); //led vystup
	sbi(DDRB,LED2);
	sbi(DDRE,LED3);
	cbi(DDRE,BUT1); //Button1 vstup
	sbi(PORTE,BUT1); //Button1 pull-up
	sbi(EIMSK,5); //povolit preruseni INT4
	sbi(EICRB,ISC51);//sestupna hrana
	//sbi(EICRB,ISC50);
	sbi(EIMSK,4); //povolit preruseni INT4
	sbi(EICRB,ISC41);//sestupna hrana
	//sbi(EICRB,ISC50);
	#endif
}
void HAL_UART_SendString(char *s)
{
	while (*s != 0x00)
	{
		HAL_UartWriteByte(*s);
		s++;
	}
}
void HAL_UART_SendInt(int cislo){
	char buff[20];
	itoa(cislo,buff,10);
	HAL_UART_SendString(buff);
}
/*
void appSendDataU(int Dest_Addr, int App_end, void *data,int delka)
{
	if (appDataReqBusy){
	HAL_UART_SendString("Error: Busy....");
	return;
	}
	appDataReq.dstAddr = Dest_Addr;
	appDataReq.dstEndpoint = App_end;
	appDataReq.srcEndpoint = App_end;
	appDataReq.options = 0;
	appDataReq.data = data;
	appDataReq.size = delka;
	//appDataReq.confirm = appDataConf;
	NWK_DataReq(&appDataReq);
	appDataReqBusy = true;
}
*/
void measure(void)
{
	#ifdef HAL_ATMEGA128RFA1
	/* measure temperature */
	TMP102_StartOneshotMeasurement();
	TMP102_GetTemperature(&temp, true);

	/* measure luminosity */
	ISL29020_StartOneshotMeasurement();
	ISL29020_GetLuminosity(&lumi);

	/* measure acceleration */
	BMA150_GetAcceleration(&accel);
	#endif
}