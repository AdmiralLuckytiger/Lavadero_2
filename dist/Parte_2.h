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
int final_lavadoV;
int finBarrera;
int finLavadoV;
int delayBarrera;
int stopBarrera;

uint8_t getPulsos(void);

int parte2(void);

int setup2(void);

int barrera(void);
int setup_barrera(void);

int lavadoV(void);
int setup_Lavado_vertical(void);

int parada2(void);

int detectar_fin_coche_lavadoV(void);

#endif /* PARTE_2_ */