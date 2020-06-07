## Variables
```c
static NWK_DataReq_t appDataReq;
static bool appDataReqBusy = false;
static uint8_t appDataReqBuffer[APP_BUFFER_SIZE];
```

## Definition of Status
```c
static void appDataConf(NWK_DataReq_t *req)
{
appDataReqBusy = false;
(void)req;
}
```

```sh
NWK_SUCCESS_STATUS                        Operation completed successfully 
NWK_ERROR_STATUS                          Unknown error 
NWK_OUT_OF_MEMORY_STATUS                  Buffer allocation failed 
NWK_NO_ACK_STATUS                         Network level acknowledgment was not received 
NWK_NO_ROUTE_STATUS                       Route to the destination address was not found 
NWK_PHY_CHANNEL_ACCESS_FAILURE_STATUS     Radio failed to gain access to the channel 
NWK_PHY_NO_ACK_STATUS                     Physical level acknowledgment was not received 
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
## Timers set
```c
static void RSSI_TimerHandler(SYS_Timer_t *timer)
{
appSendDataRSSI();
//(void)timer;
}

static void RSSI_a_TimerHandler(SYS_Timer_t *timer)
{
appSendDataRSSI();
}
```

##  
```c
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
```

## appInit
```c
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

RSSI_Timer.interval = 1000;
RSSI_Timer.mode = SYS_TIMER_PERIODIC_MODE;
RSSI_Timer.handler = RSSI_TimerHandler;

RSSI_a_Timer.interval = 60000;
RSSI_a_Timer.mode = SYS_TIMER_PERIODIC_MODE;
RSSI_a_Timer.handler = RSSI_a_TimerHandler;
}
```

## App_TaskHandler(void)
```c
static void APP_TaskHandler(void)
{
switch (appState)
{
case APP_STATE_INITIAL:
{
appInit();
appState = APP_STATE_IDLE;

if(APP_ADDR < 0x401){
SYS_TimerStart(&RSSI_Timer);
}
else if (APP_ADDR == 0x401){
SYS_TimerStart(&appTimer);
}
else if(APP_ADDR > 0x401){
SYS_TimerStart(&RSSI_a_Timer);
}

break;

case APP_STATE_IDLE:
break;

default:
break;
}
}
}
```
## States
```c
static AppState_t appState = APP_STATE_INITIAL;
```

```c
typedef enum AppState_t
{
	APP_STATE_INITIAL,
	APP_STATE_IDLE,
} AppState_t;
```

## Security
```
void NWK_SetSecurityKey(uint8_t *key)
{
  memcpy((uint8_t *)nwkIb.key, key, NWK_SECURITY_KEY_SIZE);
}
```
```c
NWK_SetSecurityKey((uint8_t *)"Security12345678"); 

NWK_SetSecurityKey((uint8_t *key); 
```
```c
PHY_EncryptReq
```
