/*
 * ECDH_MutualPoint.c
 *
 * Created: 01.06.2020 2:28:43
 *  Author: jarom
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "ECDH_Functions.h"

void MutualPoint(int *Xa, int *Ya, int *Xb, int *Yb, int *modulus, int *a_pam, int array[])
{

	int mod, a, Xi, Yi, Xj, Yj;
	static int Lambda;
	int Xk, Yk;

	mod = *modulus;
	a = *a_pam;

	Xi = *Xa;
	Yi = *Ya;

	Xj = *Xb;
	Yj = *Yb;


	int resultD = Recognizer(&Xi, &Yi, &Xj, &Yj);

	if(resultD == 1)
	{

		Lambda = LamdaSame(&mod, &Xi, &Yi, &a);
		Xk = XSame(&mod, &Lambda, &Xi);
		Yk = YSame(&mod, &Lambda, &Xi, &Yi, &Xk);

	}

	else if(resultD == 2)
	{

		Lambda = LamdaDiff(&mod, &Xi, &Yi, &Xj, &Yj);

		Xk = XDiff(&mod, &Lambda, &Xi, &Xj);
		Yk = YDiff(&mod, &Lambda, &Xi, &Yi, &Xk);
	}

	// return values
	array[0] = Xk;
	array[1] = Yk;

}

