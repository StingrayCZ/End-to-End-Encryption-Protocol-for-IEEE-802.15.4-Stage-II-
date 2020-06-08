# Konzultace 8.6.2020

## Text práce

PDF práce k nahledu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis%20862020.pdf">zde</a>. </a>

Souhrn všech spuštěcích bloků, <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Summary%20of%20ECDH%20app.md">zde</a>. </a>

Stack ke stažení v ZIP, <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Protocol%20Stack%20v2020%2086.zip">zde</a>. </a>



## App_task Handler
```c
case APP_STATE_SEND_PARAMTERES:
{
	// send array [2] p, a, b
	SYS_TimerStart(&DataSendTimer);
	
	state = APP_STATE_GOTO_PHASE_B;
	break;
	}
	
case APP_STATE_GOTO_PHASE_B:
{
	
	ECDH_PHASE_BA(&Order, &X_first, &Y_first, &a_parameter, &mod, containerB);
	
	if(containerB[0] > 0 && containerB[1] >0){
		state = APP_STATE_SEND_COMMON_POINT,;
	}
	
}


// Incializace C
//state = APP_STATE_GOTO_PHASE_C;
//break;

case APP_STATE_SEND_COMMON_POINT,:
{
	// send array [1] X, Y
	SYS_TimerStart(&DataSendTimer);
	break;
}

	// Incializace C
	//state = APP_STATE_GOTO_PHASE_C;
	//break;



case APP_STATE_GOTO_PHASE_C:
{

	ECDH_PHASE_C(&MSKey, &X_first;, &Y_first;, &X_obtain, &Y_obtain, &mod, &a_parameter, &Order, &MutKEY, containerC);
	

	break;
}

default:
break;
}
}

## Arch se všemi flowcharty (pro Key Exchange)

<p float="left">
  <img src="/Pictures (general)/SuperAll.png" width="800" /> 
<p float="left"> </p> 
```
