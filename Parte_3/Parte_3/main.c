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

	setOne(LD_DDR, DDR_L1); //Set the led 1 pin as an output
	setOne(M6_di_DDR, DDR_M6_di); //Set the M6 direction pin as an output
	setOne(M6_en_DDR, DDR_M6_en); //Set the M6 en pin as an output
	setOne(M6_di_PORT, PORT_M6_di); //Set M6 rotation direction to right

    while (1) 
    {
		x=getBit(M1_di_PORT,PORT_M1_di);
    }
}

