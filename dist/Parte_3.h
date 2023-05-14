/*
 * Parte_3.h
 *
 * Created: 24/04/2023 18:41:49
 *  Author: Eduardo Palou de Comasema Jaume 
 * version: 1.0.0
 */ 

//Librerias de trabajo 
#include "General.h"
#include "Parte_1.h"
#include "parte2.h"

#ifndef PARTE_3_H_
#define PARTE_3_H_

//Funciones de trabajo parte 3

// Parada de emergencia 
int setUpSafeStop(void);
int setCallbackSafeStop(void (*fptr)());
int SafeStop(void);
// Semaforo 
void setupLED_1(void);
void turnOnL1(void);
void turnOffL1(void);
void LED_1(void);
void LED_4_5(); 

// Cinta de arrastre 
void startBelt(void);
void stopBelt(void);
void setupBelt(void);

// Interfaz publica
void setUpParte_3(void);
void Parte_3(void);

#endif /* PARTE_3_H_ */

