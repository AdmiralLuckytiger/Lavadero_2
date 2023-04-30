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

ISR(INT0_vect){
	if(functionPointerStop != NULL) functionPointerStop();
}

ISR(TIMER3_COMPA_vect){
	if (cycle_state==CYCLE_WORKING){
		if((ms/500)%2==0 && ms%500==0){ //If ms is a pair multiple of 500
			turnOnL1();
		}
		else if((ms/500)%2==1 && ms%500==0){ //If ms is an impair multiple of 500
			turnOffL1();
		}
	}
	if (cycle_state==CYCLE_STOPPED){
		if((ms%10000)==0){
			turnOnL1();
		}
		else if((ms%10500)==0){
			turnOffL1();
		}
	}
}

void turnOnL1(){
	setOne(LD_PORT, PORT_L1);
}

void turnOffL1(){
	setZero(LD_PORT, PORT_L1);
}

void startBelt(){
	M6_en_PORT = BELT_SPEED;
}

void stopBelt(){
	M6_en_PORT = 0;
}