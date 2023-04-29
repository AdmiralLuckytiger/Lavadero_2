/*
 * Parte_3.h
 *
 * Created: 24/04/2023 18:41:49
 *  Author: Eduardo Palou de Comasema Jaume 
 * version: 1.0.0
 */ 

//Librerias de trabajo 
#include "General.h"

#ifndef PARTE_3_H_
#define PARTE_3_H_

#define CYCLE_WORKING 1
#define CYCLE_STOPPED 0
//Funciones de trabajo parte 3

int setUpSafeStop();
int setCallbackSafeStop(void (*fptr)());
int cycle_state;
void turnOnL1();
void turnOffL1();

#endif /* PARTE_3_H_ */