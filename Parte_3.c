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

void setupLED_1(){
	setOne(LD_DDR, DDR_L1); //Set the led 1 pin as an output
}

void setupBelt(){
	setOne(M6_di_DDR, DDR_M6_di); //Set the M6 direction pin as an output
	setOne(M6_en_DDR, DDR_M6_en); //Set the M6 en pin as an output
	setOne(M6_di_PORT, PORT_M6_di); //Set M6 rotation direction to right
}

ISR(INT0_vect){
	if(functionPointerStop != NULL) functionPointerStop();
}


void turnOnL1(){
	setOne(LD_PORT, PORT_L1);
}

void turnOffL1(){
	setZero(LD_PORT, PORT_L1);
}

void startBelt(){
	setOne(M6_en_PORT, PORT_M6_en);
}

void stopBelt(){
	setZero(M6_en_PORT, PORT_M6_en);
}

void LED_1(){
	readState(); 
	if (cycle_state==CYCLE_WORKING){
		if((getms()/500)%2==0 && getms()%500==0){ //If ms is a pair multiple of 500
			turnOnL1();
		}
		else if((getms()/500)%2==1 && getms()%500==0){ //If ms is an impair multiple of 500
			turnOffL1();
		}
	}
	if (cycle_state==CYCLE_STOPPED){
		if((getms()%10000)==0){
			turnOnL1();
		}
		else if((getms()%10500)==0){
			turnOffL1();
		}
	}
}

void readState(){
	uint8_t acc = 0; 
	acc += getBit(M1_en_PIN, PIN_M1_en);
	acc += getBit(M2_en_PIN, PIN_M2_en);
	acc += getBit(M3_en_PIN, PIN_M3_en);
	acc += getBit(M4_en_PIN, PIN_M4_en);
	acc += getBit(M5_en_PIN, PIN_M5_en);
	acc += getBit(M6_en_PIN, PIN_M6_en);
	if(acc>0){
		cycle_state = CYCLE_WORKING;
	}
	else{
		cycle_state = CYCLE_STOPPED; 
	}
}

