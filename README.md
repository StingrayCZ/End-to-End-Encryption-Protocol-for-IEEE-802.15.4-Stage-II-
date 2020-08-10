# Konzultace 10.8.2020

## Test prvociselnosti

<p float="left">
  <img src="/Pictures (general)/Miller.PNG" width="1500" /> 
<p float="left"> </p>

# Konzultace 7.8.2020

## Problém s oknem Watch

V okně watch mi to nezpbrazuje hodnotu... V jiném příkladě jsem to vyřešil vypnutím **Optimizace**

<p float="left">
  <img src="/Pictures (general)/Optimization.PNG" width="800" /> 
<p float="left"> </p>

<p float="left">
  <img src="/Pictures (general)/Breakpoint.PNG" width="800" /> 
<p float="left"> </p>

<p float="left">
  <img src="/Pictures (general)/ViewError.PNG" width="1200" /> 
<p float="left"> </p>

## Citace stránky s BIG N... Může to být takhle?
BigDigits multiple-precision arithmetic source code [online]. 2020 [cit. 2020-08-07]. Dostupné z: https://www.di-mgt.com.au/bigdigits.html

## Jak dostat výstup z BIGN do data (payload)?

Předpokládám, že typ **static NWK_DataReq_t appDataReq;**, resp. (**appDataReq.data = data**) asi nestráví **BIG N** proměnnou. 
P5edpoklad generování klíče z kódu níže, výstup **v**.

```C
static void appSendDataRSSItoA401(uint16_t address, uint8_t rssi_i)
{
static uint8_t data[3];

if (appDataReqBusy)
return;

data[0]=address>>8; //first 8 bits from the left
data[1]=address & 0xff; //last 8 bits
data[2]=rssi_i;

//memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

appDataReq.dstAddr = 0x401;
appDataReq.dstEndpoint = 2;
appDataReq.srcEndpoint = 2;
appDataReq.options = NWK_OPT_ENABLE_SECURITY;
appDataReq.data = data;                                                  // Toto mam na mysli
appDataReq.size = 3; //maybe more with Timestamp - will add later         // delka bude 512?
appDataReq.confirm = appDataConf;
NWK_DataReq(&appDataReq);

appUartBufferPtr = 0;
appDataReqBusy = true;
#ifdef USB_DEBUG
printf("Data sent to main anchor \n\r");
#endif
}
```

```C
BIGD v;

v = bdNew();

bdRandomSeeded(v, 508, (const unsigned char*)"", 0, my_rand);
	bdPrintHex("random=\n", v,"\n\r");
	/* NB bit length may be less than 508 */
printf("%u bits\n\r", bdBitLength(v));
  ```
