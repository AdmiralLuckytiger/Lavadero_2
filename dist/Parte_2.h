/*
 * General.c
 *
 * 	Created : 23/04/2023 18:20:57
 *  Author : Jorge Martínez de la Mata Gaitán - 18211
             Carola Adrados Herrero - 18001
             Eduardo Palou de Comasema Jaume - 18268
 *	version: 1.9.3
 *	note: 
 */ 

#include "General.h"

#ifndef PARTE_2_H_
#define PARTE_2_H_


//VARIABLES GLOBALES
uint8_t cPulsos;
char Flag_Barrera;
char Flag_Contador;
volatile uint32_t final_lavadoV;
volatile uint32_t finBarrera;
volatile uint32_t finLavadoV;
volatile uint32_t delayBarrera;
int stopBarrera;
int startLavadoV;

// INTERFAZ PUBLICA
int Parte_2(void);
int setUpParte_2(void);
int parada2(void);

// FUNCIONES BARRERA
int barrera(void);
int setup_barrera(void);

// FUNCIONES LAVADERO VERTICAL
int lavadoV(void);
int setup_Lavado_vertical(void);
void decCochesLavado(void);

#endif /* PARTE_2_ */