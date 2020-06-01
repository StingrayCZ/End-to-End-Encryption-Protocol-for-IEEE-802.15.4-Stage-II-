/*
 * ECDH_Functions.h
 *
 * Created: 28.05.2020 1:29:12
 *  Author: jarom
 */ 

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


//////////////////////////
/////  PROTOTYPES  ///////
//////////////////////////
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// ECDH_ObtainPointComplex //
void ObtainPointComplex();

// ECDH_ECDH_PointVerification //
void VerifyOfPoint();

// ECDH_Mathematics //
void PointComp();
int LamdaSame();
int LamdaDiff();
int XSame();
int XDiff();
int YSame();
int YDiff();
int Recognizer();

// ECDH_Mathematics //
int primeTester();
int modulo();
int power();
int InverseMod();

// ECDH_Order //
void checkValAB();
void TheFirstPoint();
void YPart();
void XPart();


// ECDH_SecKey //
void SecretKey();

// ECDH_MutualPoint //
void MutualPoint();

#endif // FUNCTIONS_H


/////////////////////////////
/////  PRINTF FUNCTIONS /////
/////////////////////////////

//#define PRINT_ON    // Switch ON of printf function
#define EMPTYLINE printf("\n\r");