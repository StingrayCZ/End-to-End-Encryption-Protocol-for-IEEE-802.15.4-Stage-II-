/*
 * ECDH_Functions.h
 *
 * Created: 28.05.2020 1:29:12
 *  Author: jarom
 */ 

#include <time.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void ObtainPointComplex();

void PointComp();
void VerifyOfPoint();
int LamdaSame();
int LamdaDiff();
int XSame();
int XDiff();
int YSame();
int YDiff();
int Recognizer();

int modulo();
void moduloVOID();

int power();
int InverseMod();
int primeTester();



void YPart();
void XPart();
void TheFirstPoint();
void checkValAB();

#endif // FUNCTIONS_H






#ifndef AUX_FUNCT
#define AUX_FUNCT

#define EMPTYLINE printf("\n\r");

#endif // AUX_FUNCT
