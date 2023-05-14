#include "General.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>


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