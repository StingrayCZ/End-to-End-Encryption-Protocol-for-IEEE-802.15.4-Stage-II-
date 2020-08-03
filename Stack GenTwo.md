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
