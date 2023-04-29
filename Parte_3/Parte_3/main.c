/*
 * Parte_3.c
 *
 * Created: 23/04/2023 16:51:46
 * Author : Edu Palou de Comasema Jaume, Damien ...
 */ 

#include <avr/io.h>
#include "General.h"
uint32_t x = 0;
int main(void)
{
    /* Main de pruebas */
	setupTimers();

	setOne(M1_di_PORT,PORT_M1_di);
	x=getBit(M1_di_PORT,PORT_M1_di);
	setZero(M1_di_PORT,PORT_M1_di);
	x=getBit(M1_di_PORT,PORT_M1_di);

	setOne(LD_DDR, DDR_L1); //Set the led one to output

    while (1) 
    {
		x=getBit(M1_di_PORT,PORT_M1_di);
    }
}

