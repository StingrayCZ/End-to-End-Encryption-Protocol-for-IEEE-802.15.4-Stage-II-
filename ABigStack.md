# Stack
## FullStack ver

```C



static void RSSI_a_TimerHandler(SYS_Timer_t *timer)
{
appSendDataRSSI();  // Payload
}

///////////////////////////////////////////////////////////////////////////////////

static bool appAnchorData(NWK_DataInd_t *ind)
{

uint16_t address = ind->srcAddr;
volatile uint16_t NodeAddress;
volatile uint16_t NodeAddressa;
volatile uint16_t NodeAddressb;
NodeAddressa= ind->data[0]<<8;
NodeAddressb= ind->data[1];

NodeAddress= NodeAddressa + NodeAddressb;

int8_t rssiX=ind->data[2];
#ifdef USB_DEBUG
printf("We got data from anchor %d: Node: %d, RSSI: %d\n\r", address,NodeAddress,rssiX);
#endif

LED0SW;
//other lines
matrix[address-0x401][NodeAddress-1] = rssiX;
return true;

}

///////////////////////////////////////////////////////////////////////////////

// Insert to appInit
NWK_OpenEndpoint(2, appAnchorData);

appTimer.interval = APP_FLUSH_TIMER_INTERVAL;
appTimer.mode = SYS_TIMER_PERIODIC_MODE;
appTimer.handler = appTimerHandler;


///////////////////////////////////////////////////////////////////////////////

// Insert to APP_TaskHandler
SYS_TimerStart(&RSSI_Timer);
```

## Variables
```C
static NWK_DataReq_t appDataReq;     // appDataReq.dstAddr = 1-APP_ADDR;  payload...
static bool appDataReqBusy = false;   //  
static uint8_t appDataReqBuffer[APP_BUFFER_SIZE];
```

## Payload busy
```C
static void appDataConf(NWK_DataReq_t *req)
{
appDataReqBusy = false;
(void)req;
}
````

## Payload busy

```C
/*************************************************************************//**
*****************************************************************************/
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

## Timer

```C
static void appTimerHandler(SYS_Timer_t *timer)
{
printTable();
(void)timer;
}
```
## Receive data

```C
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
```

## AppInit

```C
static void appInit(void)
{
NWK_SetAddr(APP_ADDR);
NWK_SetPanId(APP_PANID);
PHY_SetChannel(APP_CHANNEL);
#ifdef PHY_AT86RF212
PHY_SetBand(APP_BAND);
PHY_SetModulation(APP_MODULATION);
#endif
PHY_SetRxState(true);

if(APP_ADDR > 0x400){
NWK_OpenEndpoint(APP_ENDPOINT, appDataInd);
}

if(APP_ADDR == 0x401){
NWK_OpenEndpoint(2, appAnchorData);
}

if(APP_ADDR < 0x400){
NWK_OpenEndpoint(APP_ENDPOINT, appAnchorData);
}

HAL_BoardInit();
BoardInit();

appTimer.interval = APP_FLUSH_TIMER_INTERVAL;
appTimer.mode = SYS_TIMER_PERIODIC_MODE;
appTimer.handler = appTimerHandler;

}
```
