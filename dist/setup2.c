#include "Parte_2.h"

//GLOBAL A LAS 4 FUNCIONES
int setup2(void){
	
	//INT3
	EICRA |= 0b11000000
	EIMSK |= 0b00001000	
	//setup barrera
	setup_barrera();	
	
	//setup Lavado vertical
	setup_Lavado_vertical();
	
	return 0;
}

//ISR INTERRUPCIONES
//
ISR(INT3_vect){
	cPulsos++;
}
