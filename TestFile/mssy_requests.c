/*
 * mssy_requests.c
 *
 * Created: 6.4.2017 16:12:28
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

//#include "astudio/buffer.h"

void Req_text(int dest)
{
	static char text[8]="TestOdK";
	appSendDataU(dest,2,text,8);
	HAL_UART_SendString("Done send text \n\r");
}
void Req_NeighbDisc(){
	appSendDataU(0xFFFF,8,0, sizeof(0));
};
void Req_LED(int addr,uint8_t LED,uint8_t stav){
	static char data[4]={0,0,0,0};
	data[0]=LED;
	data[3]=stav;
	
	appSendDataU(addr,6,data,4);
}
void Req_Data(int addr,uint8_t data, uint8_t typ){
	static uint8_t specifikace[2];
	specifikace[0]=data;
	specifikace[1]=typ;
	//char text[10]="pepa";
	appSendDataU(addr,3,specifikace,2);
}
void Send_Data_Event(int addr,uint8_t data, uint8_t typ){
	
	static uint8_t specifikace[2];
	specifikace[0]=data;
	specifikace[1]=typ;
	//char text[10]="pepa";
	appSendDataU(addr,4,specifikace,2);
}
void Send_Data_Neighbors(){
	uint8_t *data;
	data = (uint8_t *) malloc(Sousede.pocet*2*sizeof(uint8_t));
	
	//static uint8_t data[30];
	for (int i=0;i<=Sousede.pocet;i++)
	{
		data[2*i]=Sousede.soused[i].Addr;
		data[2*i+1]=Sousede.soused[i].RSSI;
		//data[3*i+2]=Sousede.soused[i].RSSI;
		
	}
	appSendDataU(0,7,data,2*(Sousede.pocet));
	
}
uint16_t Req_Addr(){
	uint16_t *seed;
	seed = (uint16_t *) malloc(sizeof(uint16_t));
	*seed=PHY_RandomReq();
	appSendDataU(0,15,seed,2);
	return *seed;	
}