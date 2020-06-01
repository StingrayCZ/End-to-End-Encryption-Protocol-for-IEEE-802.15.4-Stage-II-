/*
 * mssy_endpoints.c
 *
 * Created: 6.4.2017 15:03:07
 *  Author: Krajsa
 */ 
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
#include "mssy_functions.h"
#include "mssy_requests.h"
#include "main.h"
#include "ADC_lib.h"

/*- Definitions ------------------------------------------------------------*/

bool appText(NWK_DataInd_t *ind){
HAL_UART_SendString("\n\r Textova zprava od uzlu ");
HAL_UART_SendInt(ind->srcAddr);
HAL_UART_SendString(": ");

for(int i=0;i<(ind->size);i++){
	HAL_UartWriteByte(ind->data[i]);

}

HAL_UART_SendString("\n\r");
/*char text[10]="OK";
appSendDataU(ind->srcAddr,2,text,4);
*/
return true;
}
bool appGet_Data_req(NWK_DataInd_t *ind){
	//char pom_text[30]="2";
	int pom_data=0;
	int delka=0;
	uint8_t *datas;
	datas = (uint8_t *) malloc(12);
	//static uint8_t datas[12]={0,0,0,0,0,0,0,0,0,0,0,0};
		
	switch (ind->data[0]){
		case 1:
		pom_data=ADC_readTemp();
		datas[0]=ind->data[0];
		datas[1]=3;
		datas[2]=(pom_data >> 8) & 0xFF;
		datas[3]=pom_data & 0xFF;
		delka=4;
		break;
		case 2:
		pom_data=ADC_get(0);
		datas[0]=ind->data[0];
		datas[1]=3;
		datas[2]=(pom_data >> 8) & 0xFF;
		datas[3]=pom_data & 0xFF;
		delka=4;
		break;
		case 16: //teplota
		datas[0]=16;
		datas[1]=255;
		datas[2]=temp.sign;
		datas[3]=temp.integralDigit;
		datas[4]=temp.fractionalDigit;
		delka=5;		
		break;
		case 17: //svetlo
		datas[0]=ind->data[0];
		datas[1]=7;
		datas[2]=(lumi >> 8) & 0xFF;
		datas[3]=lumi & 0xFF;
		delka=4;
		break;
		}
	
	appSendDataU(ind->srcAddr,ind->srcEndpoint,datas,delka);
	
	
	/*	
	if(APP_ADDR==0){
		
		switch (ind->data[0]){
		case 1:
		strncpy(pom_text, "Teplota CPU", 30);
		
		break;
		case 2:
		strncpy(pom_text, "A0", 30);
		break;
		case 3:
		strncpy(pom_text, "A1", 30);
		break;
	}
	switch (ind->data[1]){
		case 1:
		pom_data=ind->data[2];
		break;
		case 2:
		pom_data=ind->data[2];
		break;
		case 3:
		pom_data=ind->data[2]<<8 | ind->data[3];
		break;
	}
	
	HAL_UART_SendString(pom_text);
	HAL_UART_SendString(" od uzlu ");
	HAL_UART_SendInt(ind->srcAddr);
	HAL_UART_SendString(": ");
	HAL_UART_SendInt(pom_data);
	HAL_UART_SendString(" \n\r");
		
	}
	else{
		static uint8_t data[4]={0,0,0,0};
		switch (ind->data[0]){
		case 1:
		strncpy(pom_text, "Zadost o teplotu CPU", 30);
		pom_data=ADC_readTemp();
		break;
		case 2:
		strncpy(pom_text, "Zadost o  A0", 30);
		pom_data=ADC_get(0);
		break;
		case 3:
		strncpy(pom_text, "Zadost o  A1", 30);
		pom_data=ADC_get(1);
		break;
	}
	switch (ind->data[1]){
		case 1:
		data[0]=ind->data[0];
		data[1]=ind->data[1];
		data[2]=(pom_data >> 8) & 0xFF;
		break;
		case 2:
		data[0]=ind->data[0];
		data[1]=ind->data[1];
		data[2]=(pom_data >> 8) & 0xFF;
		break;
		case 3:
		data[0]=ind->data[0];
		data[1]=ind->data[1];
		data[2]=(pom_data >> 8) & 0xFF;
		data[3]=pom_data & 0xFF;
		break;
	}
	
	HAL_UART_SendString(pom_text);
	HAL_UART_SendString(" od uzlu ");
	HAL_UART_SendInt(ind->srcAddr);
	HAL_UART_SendString(" je:  ");
	HAL_UART_SendInt(pom_data);
	HAL_UART_SendString("\n\r");
	appSendDataU(ind->srcAddr,ind->srcEndpoint,data,4);	
	}
	
	*/
return true;

}
bool appGet_Data_event(NWK_DataInd_t *ind){
	
char pom_text[15]="2";
int pom_data=0;
	switch (ind->data[0]){
		case 1:
		strncpy(pom_text, "Teplota CPU", 15);
		
		break;
		case 2:
		strncpy(pom_text, "A0", 15);
		break;
		case 3:
		strncpy(pom_text, "A1", 15);
		break;
		}
	switch (ind->data[1]){
		case 1:
		pom_data=ind->data[2];	
		break;
		case 2:
		pom_data=ind->data[2];		
		break;
		case 3:
		pom_data=ind->data[2]<<8 | ind->data[3];
		break;
	}
	/*
HAL_UART_SendString(pom_text);
HAL_UART_SendString(" od uzlu ");
HAL_UART_SendInt(ind->srcAddr);
HAL_UART_SendString(": ");
HAL_UART_SendInt(pom_data);
HAL_UART_SendString(" \n\r");
*/
return true;
}
bool appGet_Data_per(NWK_DataInd_t *ind){
char pom_text[15]="1";
int pom_data=0;
switch (ind->data[0]){
	case 1:
	strncpy(pom_text, "Teplota CPU", 15);
	break;
	case 2:
	strncpy(pom_text, "A0", 15);
	break;
	case 3:
	strncpy(pom_text, "A1", 15);
	break;
}
switch (ind->data[1]){
	case 1:
	pom_data=ind->data[2];
	break;
	case 2:
	pom_data=ind->data[2];
	break;
	case 3:
	pom_data=ind->data[2]<<8 | ind->data[3];
	break;
}
/*
HAL_UART_SendString(pom_text);
HAL_UART_SendString(" od uzlu ");
HAL_UART_SendInt(ind->srcAddr);
HAL_UART_SendString(": ");
HAL_UART_SendInt(pom_data);
HAL_UART_SendString(" \n\r");
*/
return true;	
}
bool appLEDswap(NWK_DataInd_t *ind)
{
	switch (ind->data[0]){
		case 13:
		if(ind->data[3]){
			cbi(PORTG,LED0);
		}
		else
		sbi(PORTG,LED0);
		break;
		case 14:
		if(ind->data[3]){
			cbi(PORTE,LED1);
		}
		else
		sbi(PORTE,LED1);
		break;
		case 15:
		if(ind->data[3]){
			cbi(PORTE,LED2);
		}
		else
		sbi(PORTE,LED2);
		break;
	
		
	}


	
return true;
	
}
bool appNeighbCoordinator(NWK_DataInd_t *ind){
	/*HAL_UART_SendString("Sousede uzlu ");
	HAL_UART_SendInt(ind->srcAddr);
	HAL_UART_SendString(": \n\r ");
	for(int i=0;i<(ind->size)/2;i++){
		HAL_UART_SendString("Soused ");
		HAL_UART_SendInt(i);
		HAL_UART_SendString("Adresa: ");
		HAL_UART_SendInt(ind->data[i*2]);
		HAL_UART_SendString(" RSSI: ");
		HAL_UART_SendInt(ind->data[(i*2)+1]);
		HAL_UART_SendString("\n\r");
	}
	*/
return true;	
}
bool appNeighbDisc(NWK_DataInd_t *ind){
	
	
	if(ind->dstAddr==0xFFFF){
		/*HAL_UART_SendString("B - RSSI od souseda ");
		HAL_UART_SendInt(ind->srcAddr);
		HAL_UART_SendString(": ");
		HAL_UART_SendInt(ind->rssi);
		HAL_UART_SendString("\n\r");
		HAL_UART_SendString("LQI od souseda ");
		HAL_UART_SendInt(ind->srcAddr);
		HAL_UART_SendString(": ");
		HAL_UART_SendInt(ind->lqi);
		HAL_UART_SendString("\n\r");*/
		appSendDataU(ind->srcAddr,8,0, sizeof(0));
	}
	else{
			/*HAL_UART_SendString("U - RSSI od souseda ");
			HAL_UART_SendInt(ind->srcAddr);
			HAL_UART_SendString(": ");
			HAL_UART_SendInt(ind->rssi);
			HAL_UART_SendString("\n\r");
			HAL_UART_SendString("LQI od souseda ");
			HAL_UART_SendInt(ind->srcAddr);
			HAL_UART_SendString(": ");
			HAL_UART_SendInt(ind->lqi);
			HAL_UART_SendString("\n\r");
			*/
			bool existuje = false;
			int misto=0;
			for (int i=0;i<Sousede.pocet;i++)
			{
				if(Sousede.soused[i].Addr==ind->srcAddr){
					existuje=true;
					misto=i;
					}	
				
			}
			if (existuje==false){
				Sousede.soused[Sousede.pocet].Addr=ind->srcAddr;
				Sousede.soused[Sousede.pocet].RSSI=ind->rssi;
				Sousede.pocet=Sousede.pocet+1;
			}
			if (existuje==true){
				//Sousede.soused[misto].Addr=ind->srcAddr;
				Sousede.soused[misto].RSSI=ind->rssi;
			}	

	
	}

return true;
}
bool appGetAddress(NWK_DataInd_t *ind){
	uint16_t pom1;
	uint8_t pom2;
	pom2=ind->data[2];
	memcpy(&pom1,ind->data,2);
	if(pom1==AddrSeed){
	tempAddr=pom2;
	//LED2SW;		
	}
	return true;
	
}