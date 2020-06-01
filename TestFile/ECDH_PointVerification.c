/*
 * ECDH.c
 *
 * Created: 29.05.2020 3:09:13
 *  Author: jarom
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "ECDH_Functions.h"

//////////////////////////////////
//// VERIFY POINT ////////////////
//////////////////////////////////
void VerifyOfPoint(int *modulus, int *X, int *Y, int *a, int *b, int *returnVAl){

	int mod, x, y, a_pam, b_pam;
	int pow_x, pow_y;

	int resX, resY;

	mod = *modulus;
	x = *X;
	y = *Y;
	a_pam = *a;
	b_pam = *b;

	pow_x = 3;
	pow_y = 2;

	resX = power(&x,&pow_x);
	resX += (a_pam * x + b_pam) ;
	resX = modulo(&resX, &mod);

	resY = power(&y,&pow_y);
	resY = modulo(&resY, &mod);

	if(resX == resY){

		*returnVAl = 1;
	}
	else{
		*returnVAl = 66;
	}

}
