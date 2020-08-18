# Konzultace 18.8.2020

```C
// Variables
BB MOD, a_parameter, b_parameter;
volatile BB resultsA[2];

// Faze B 
BB Order, Xf, Yf;
volatile BA results[];
volatile BB results[];

// Faze C
BB Xm, Ym, Xo, Yo, KEY;

MOD = bdNew();
a_parametr = bdNew();
b_parametr = bdNew();
resultsA[0] = bdNew();
resultsA[1] = bdNew();
resultsA[2] = bdNew();
Order = bdNew();
Xf = bdNew();
Yf = bdNew();

resultsBA[0] = bdNew();
resultsBA[1] = bdNew();
resultsBA[2] = bdNew();

resultsBB[0] = bdNew();
resultsBB[1] = bdNew();
resultsBB[2] = bdNew();

Xm = bdNew();
Ym = bdNew();
Xo = bdNew();
Yo = bdNew();
KEY = bdNew();
```

```C
// Faze A
ECDH_PHASE_A_BIGD(MOD, a_parameter, b_parameter, resultsA);
// Aplikace voli 
// Generuje pole: resultsA[0]->xf
                  resultsA[1]->yf
		  resultsA[2]->Order


// Faze B (deska A)
ECDH_PHASE_BA_BIGD(Order, Xf, Yf, a_parameter, MOD, BB resultsBA);
Vstup: Order, Xf, Yf, a_parameter
Vystup: 



// Face B (deska B)
ECDH_PHASE_BB_BIGD(MOD, a_parameter, b_parameter, resultsBB);


// Face C
ECDH_PHASE_C_BIGD(Xm, Ym, Xo, Yo, MOD, a_parameter, BB KEY);
```


# 1# Otazka - 

<p float="left">
  <img src="/Pictures (general)/PicError.PNG" width="800" /> 
</p>

```C
static void SendDataA(void)
{
	adata[0]=address>>8; //first 8 bits from the left
	data[1]=address & 0xff; //last 8 bits
	data[2]=rssi_i;


	appDataReq.dstAddr = 0xFFFF;
	appDataReq.dstEndpoint = 2;
	appDataReq.srcEndpoint = 1;
	//appDataReq.options = NWK_OPT_ENABLE_SECURITY;
	appDataReq.data = data;
	appDataReq.size = 3;
	appDataReq.confirm = appDataConf;
	NWK_DataReq(&appDataReq);                           // odeslani dat


	appDataReqBusy = true;
	
	
	// Posilam data data
	printf("Odeslana data: ", appDataReq.data);
	
}



static bool PHASE_A(NWK_DataInd_t *ind)
{ 

 ECDH_PHASE_A_BIGD(MOD, a_parameter, b_parameter, resultsA);
 
 

}
```


