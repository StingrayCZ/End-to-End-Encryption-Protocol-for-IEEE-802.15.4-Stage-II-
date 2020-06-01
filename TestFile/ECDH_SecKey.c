/*
 * ECDH_SecKey.c
 *
 * Created: 01.06.2020 0:22:07
 *  Author: jaromir
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "ECDH_functions.h"



void SecretKey(int *OrderG, int*SecKey)
{
	static int order, result;

	order = *OrderG;

	result = rand() % (order  - 2);
	
	// Uprage due to solution of PointComp algorithm (order - 2) => elimination of first point end zero-point
	if(result == 2)
	{
		result += 1;
	}
	else if(result == 1)
	{
		result += 2;
	}
	else if(result == 0)
	{

		result += 3;
	}

	*SecKey = result;
}