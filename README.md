# Konzultace 18.8.2020

Stack ke stazeni <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Stack%2018%208%202020.zip">zde</a>.

# 1# Otazka - my_rand

V aplikacich **ECDH_Phase_A_Big** a **SecretKey_Big** je naimplentovana aplikace **my_rand**, dle knihovny **t_bdTest.c**. Nevim, proc, ale kompilator mi hlasi problem z dablovanou promenou, coz neni mozne. Aplikace je vlozena do kazde aplikace jednou a nemeli by se ovlivnpvat.

<p float="left">
  <img src="/Pictures (general)/PicError.PNG" width="800" /> 
</p>


# 2# Otazka - posilani dat mezi deskami

Jak spravne odeslat pole velkych cisel? Je potreba prevest na oktety (blok nize)?

```C
volatile BIGD number;

int delka;
uint8_t *array;

number = bdNew();

delka = bdConvToOctets(number, NULL, 0);
array = malloc(delka);
bdConvToOctets(number, array, delka);
```

```C
static void SendDataA(void)
{
	BB data[6];
	
	data[0] = bdNew();
	data[1] = bdNew();
	data[2] = bdNew();
	data[3] = bdNew();
	data[4] = bdNew();
	data[5] = bdNew();
	
	
	data[0] = MOD;
	data[1] = a_parameter; 
	data[2] = b_parameter;
	data[3] = resultsA[0];  // Xf
	data[4] = resultsA[1];  // Yf
	data[5] = resultsA[2];  // Order
 

	appDataReq.dstAddr = 0xFFFF;
	appDataReq.dstEndpoint = 2;
	appDataReq.srcEndpoint = 1;
	//appDataReq.options = NWK_OPT_ENABLE_SECURITY;
	appDataReq.data = data;
	appDataReq.size = 7;
	appDataReq.confirm = appDataConf;
	NWK_DataReq(&appDataReq);


	appDataReqBusy = true;
	
	
	// Posilam data data
	printf("Odeslana data: ", appDataReq.data);
	
}



static bool PHASE_A(NWK_DataInd_t *ind)
{ 

 ECDH_PHASE_A_BIGD(MOD, a_parameter, b_parameter, resultsA);
 
 

}
```
# 3# Otazka - prijimani dat... 

Toto asi bude fungovat. Ovsem je zde problem s mazanim objektu. Pokud je smazu pomoci, treba bdFree(&Mod), tak ulozena hodnota se ztrati. </br>

Spusteni Faze A
```C
static void APP_TaskHandler(void)
{
	

	MOD = bdNew();
	a_parameter = bdNew();
	b_parameter = bdNew();
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
	
	
switch (appState)
{
case APP_STATE_Init:
{
	appInit();
	appState = APP_STATE_FazeA;

} break;

case APP_STATE_FazeA
{ 
	ECDH_PHASE_A_BIGD(MOD, a_parameter, b_parameter, resultsA);
	
	
}
```

</br>
Odeslani dat z Faze

```C
static bool SendFromAToB_BB(NWK_DataInd_t *ind)  // Version BA
{
        // aktivace bloku
	MOD = bdNew();
	a_parameter = bdNew();
	b_parameter = bdNew();
	resultsBB[0] = bdNew();
	resultsBB[1] = bdNew();

	MOD = ind->data[0];
	a_parameter = ind->data[1];
	a_parameter = ind->data[2];
	
	ECDH_PHASE_BB_BIGD(MOD, a_parameter, b_parameter, resultsBB);
	
	// odeslat data??
	
	// proces mazani
	bdFree(&MOD)
	
	
}

static bool SendFromAToB_BB(NWK_DataInd_t *ind)  // Version BA
{
	MOD = bdNew();
	resultsBB[0] = bdNew();  // souradnice X
	resultsBB[1] = bdNew();  // souradnice Y

	MOD = ind->data[0];
	a_parameter = ind->data[1];
	a_parameter = ind->data[2];
	
	ECDH_PHASE_BB_BIGD(MOD, a_parameter, b_parameter, resultsBB);
	
	
}

```

## ECDH Componets

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
Vystup: results[0] // X
        results[1] // Y
	results[2] // Order



// Face B (deska B)
ECDH_PHASE_BB_BIGD(MOD, a_parameter, b_parameter, resultsBB);
Vystup: 

// Face C
ECDH_PHASE_C_BIGD(Xm, Ym, Xo, Yo, MOD, a_parameter, BB KEY);
```

