#include <stdio.h>
#include "function.h"
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
int modulo (long *num, long *mod)
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
int power(long *num, long *power)
{

	long numpow = *num;

	for(int i = 1; i < *power; i++)
	{

		numpow *= *num;
	}

	return numpow;
}


//////////////////////////////////
//// INVERSE MODULO //////////////
//////////////////////////////////
int InverseMod(long *Num, long *Mod)
{

	long usageNum, multiplier, result;

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

		multiplier -= 1; // vyrušení p?ebyte?ného inkrementu

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

		multiplier -= 1; // vyrušení p?ebyte?ného inkrementu

		multiplier = *Mod - multiplier;  // Specialni uprava pro zaporne cislo

		return multiplier;
	}

	return 0;
}
