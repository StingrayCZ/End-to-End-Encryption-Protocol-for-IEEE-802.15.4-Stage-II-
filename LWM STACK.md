## Definition of Status
```c
static void appDataConf(NWK_DataReq_t *req)
{
appDataReqBusy = false;
(void)req;
}
```

```sh
NWK_SUCCESS_STATUS Operation completed successfully 
NWK_ERROR_STATUS Unknown error 
NWK_OUT_OF_MEMORY_STATUS Buffer allocation failed 
NWK_NO_ACK_STATUS Network level acknowledgment was not received 
NWK_NO_ROUTE_STATUS Route to the destination address was not found 
NWK_PHY_CHANNEL_ACCESS_FAILURE_STATUS Radio failed to gain access to the channel 
NWK_PHY_NO_ACK_STATUS Physical level acknowledgment was not received 
```

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
