#include "parte2.h"

//GLOBAL A LAS 4 FUNCIONES
int setUpParte_2(void){
	cli();
	//INT3
	EICRA |= 0b11000000;
	EIMSK |= 0b00001000;
	//setup barrera
	setup_barrera();	
	
	//setup Lavado vertical
	setup_Lavado_vertical();
	sei();
	return 0;
}

//ISR INTERRUPCIONES
//


ISR(INT3_vect){
	cPulsos++;
}

