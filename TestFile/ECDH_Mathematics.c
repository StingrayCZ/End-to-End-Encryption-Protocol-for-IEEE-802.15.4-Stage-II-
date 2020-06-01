/*
 * ECDH_Mathematics.c
 *
 * Created: 28.05.2020 1:40:56
 *  Author: jarom
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "ECDH_functions.h"
#include <stdbool.h>

///////////////////
//// Primality ////
///////////////////
int primeTester(int *num, int *result)
{

	static int cislo, boolean;

	cislo = *num;
	boolean = true;

	for(int i = cislo - 1; i > 1; i--)
	{
		if(cislo % i == 0)    // for example 4 mod3 = 1; 4 mod2 = 0 => there is no reminder
		{
			boolean = false;
		}
	}

	if(boolean)
	{
		return 1;
	}
	else
	{
		return 2;
	}

	return 0;
}



//////////////////////////////////
//// MODULO //////////////////////
//////////////////////////////////f
int modulo (int *num, int *mod)
{

	long tempNum = *num;

	if(tempNum > 0) // Je kladne
	{
		tempNum %= *mod;    // Vypocet modula

		return tempNum;     // Navrat vypocitane hodnoty cyklu
	}

	else if(tempNum < 0)  // Je zaporne
	{
		tempNum *= (-1);  // uprava cisla zpet na kladne

		tempNum %= *mod;  // Vypocet modula

		tempNum = *mod - tempNum;  // Specialni uprava pro zaporne cislo

		return tempNum;    // Navrat vypocitane hodnoty cyklu
	}

	return 0;
}

//////////////////////////////////
//// POWER ///////////////////////
//////////////////////////////////
int power(int *num, int *power)
{

	int numpow = *num;

	for(int i = 1; i < *power; i++)
	{

		numpow *= *num;
	}
	
	return numpow;
}


//////////////////////////////////
//// INVERSE MODULO //////////////
//////////////////////////////////
int InverseMod(int *Num, int *Mod)
{

	int usageNum, multiplier, result;

	usageNum = *Num;
	multiplier = 1;

	if(usageNum > 0)  // Je kladne
	{
		do
		{
			result = (usageNum * multiplier) % *Mod;
			multiplier++;
		}
		while (result >= 2);

		multiplier -= 1; // vyru�en� p?ebyte?n�ho inkrementu

		return multiplier;
	}

	else if (usageNum < 0) // Je zaporne
	{
		usageNum *= (-1);  // uprava cisla zpet na kladne

		do
		{
			result = (usageNum * multiplier) % *Mod;
			multiplier++;
		}
		while (result >= 2);

		multiplier -= 1; // vyru�en� p?ebyte?n�ho inkrementu

		multiplier = *Mod - multiplier;  // Specialni uprava pro zaporne cislo

		return multiplier;
	}

	return 0;
}