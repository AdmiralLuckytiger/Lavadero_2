#include "General.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>


#ifndef PARTE_2_
#define PARTE_2_


//VARIABLES 

uint8_t cPulsos;

char Flag_Barrera;
char Flag_Contador;
volatile uint32_t final_lavadoV;
volatile uint32_t finBarrera;
volatile uint32_t finLavadoV;
volatile uint32_t delayBarrera;
int stopBarrera;
int startLavadoV;

uint8_t getPulsos(void);

int Parte_2(void);

int setUpParte_2(void);

int barrera(void);
int setup_barrera(void);

int lavadoV(void);
int setup_Lavado_vertical(void);

int parada2(void);

int detectar_fin_coche_lavadoV(void);

void decCochesLavado(void);

#endif /* PARTE_2_ */