# Stack

## Definice Payloadu
```C
static void appDataConf(NWK_DataReq_t *req)
{
	appDataReqBusy = false;
	(void)req;
}
```

```C
static void appECDH_Payload_parameters(void)
{
if (appDataReqBusy)
return;

int64_t DataSend[3];

DataSend[0] = mod;
DataSend[1] = a_parameter;
DataSend[2] = b_parameter;

//memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

appDataReq.dstAddr = 0xFFFF;
appDataReq.dstEndpoint = APP_ENDPOINT;
appDataReq.srcEndpoint = APP_ENDPOINT;
appDataReq.options = NWK_OPT_ENABLE_SECURITY;
appDataReq.data = DataSend;
appDataReq.size = sizeof(DataSend);
appDataReq.confirm = appDataConf;
NWK_DataReq(&appDataReq);


appDataReqBusy = true;

#ifdef PRINT_ON
printf("Data sent \n\r");
#endif
}
```

## appInit
```C
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


NWK_OpenEndpoint(2, appECDHDataReceiver);



//HAL_BoardInit();
//BoardInit();




DataSendTimer.interval = 600;
DataSendTimer.mode = SYS_TIMER_PERIODIC_MODE;
DataSendTimer.handler = DataSendTimerHandlerParameters;


DataSendTimerSharedKey.interval = 600;
DataSendTimerSharedKey.mode = SYS_TIMER_PERIODIC_MODE;
DataSendTimerSharedKey.handler = DataSendTimerHandlerSharedKey;


}

```
