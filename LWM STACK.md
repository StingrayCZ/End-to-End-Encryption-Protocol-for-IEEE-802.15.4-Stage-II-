## Definition of payload

```c
static void appSendDataRSSI(void)
{
if (appDataReqBusy)
return;

//memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

appDataReq.dstAddr = 0xFFFF;
appDataReq.dstEndpoint = APP_ENDPOINT;
appDataReq.srcEndpoint = APP_ENDPOINT;
appDataReq.options = NWK_OPT_ENABLE_SECURITY;
appDataReq.data = 65;
appDataReq.size = 1;
appDataReq.confirm = appDataConf;
NWK_DataReq(&appDataReq);

appUartBufferPtr = 0;
appDataReqBusy = true;
#ifdef USB_DEBUG
printf("Data sent \n\r");
#endif
LED0SW;
}
```
