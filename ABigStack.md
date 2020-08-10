# Stack

```C
static void appDataConf(NWK_DataReq_t *req)
{
appDataReqBusy = false;
(void)req;
}

/*************************************************************************//**
*****************************************************************************/
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

## Timer

```C
static void appTimerHandler(SYS_Timer_t *timer)
{
printTable();
(void)timer;
}
```
## Receive data
static bool appDataInd(NWK_DataInd_t *ind)
{

//for (uint8_t i = 0; i < ind->size; i++)
//HAL_UartWriteByte(ind->data[i]);

uint16_t address = ind->srcAddr;
int8_t rssi_i = ind->rssi;

#ifdef USB_DEBUG
printf("We got data from node %d, RSSI is %d\n\r", address,rssi_i);
#endif

if(APP_ADDR != 0x401){
appSendDataRSSItoA401(address, rssi_i);
}
if(APP_ADDR == 0x401){
//check if the address is under 0x401 or over - data to anchorTable
if(address > 0x401){
	anchorTable[0][address-0x402] = rssi_i;
}
else if(address < 0x401){
	matrix[0][address-1] = rssi_i;
}
//matrix_distance[0][address-1] = calculateDistances();	??????????????????????????????????????????????????
}
