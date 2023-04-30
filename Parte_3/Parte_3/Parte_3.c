/*
 * Parte_3.c
 *
 * Created: 24/04/2023 18:42:29
 *  Author: Eduardo Palou de Comasema Jaume
 * version: 1.0.0
 */ 

#include "Parte_3.h"

//Variables Globales
void (*functionPointerStop)();

//Funciones de trabajo 
int setUpSafeStop(){
	EICRA |= 0b00000011;
	EIMSK |= 0b00000001;
return 0;
}

int setCallbackSafeStop(void (*fptr)()){
	functionPointerStop = fptr;
return 0;
}

int SafeStop(){
	// Stop barrier

	// Stop vertical brushes

	// Stop horizontal brushes

	// Stop horizontal drayer

	// Wait until btn is unpressed

	// Get down barrier

	// Get down vertical brushes

	// Get down horizontal brushes

	// Stop horizontal drayer

	// Wait until reset

return 0;
}

int blockCarWhash(){
	// Inabilitate motors and Leds

	// Wait until reset

return 0;
}
//////////////////////////////////////////////////////////
// Interruptions
ISR(INT0_vect){
	if(functionPointerStop != NULL) functionPointerStop();
}