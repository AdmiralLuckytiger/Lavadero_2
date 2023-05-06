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

// Parada de emergencia
/**
 * @brief Configure the routine for an emergency stop
 * 
 * @return int 
 */
int SafeStop(void) {
	stopBelt();
	parada_emergencia();
return 0;
}

/**
 * @brief Set the registers of the interrupt INT0
 * 
 * @return int 
 */
int setUpSafeStop(){
	EICRA |= 0b00000011;
	EIMSK |= 0b00000001;
	setCallbackSafeStop(SafeStop);
return 0;
}
/**
 * @brief Set the Callback Safe Stop object
 * 
 * @param fptr 
 * @return int 
 */
int setCallbackSafeStop(void (*fptr)()){
	functionPointerStop = fptr;
return 0;
}

// Semaforo
/**
 * @brief Set register of LED_1
 * 
 */
void setupLED_1(){
	setOne(LD_DDR, DDR_L1); //Set the led 1 pin as an output
}
/**
 * @brief Turn on the LED_1
 * 
 */
void turnOnL1(){
	setOne(LD_PORT, PORT_L1);
}
/**
 * @brief Turn off the LED_1
 * 
 */
void turnOffL1(){
	setZero(LD_PORT, PORT_L1);
}
/**
 * @brief Set the behavior of LED_1
 * 
 */
void LED_1(){
	int cycle_state = getState(); 
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
	}
}
// Cinta de arrastre 
/**
 * @brief Setup the registers of the belt
 * 
 */
void setupBelt(){
	setOne(M6_di_DDR, DDR_M6_di); //Set the M6 direction pin as an output
	setOne(M6_en_DDR, DDR_M6_en); //Set the M6 en pin as an output
	setOne(M6_en_PORT, PORT_M6_en); //Set M6 rotation direction to right
}
/**
 * @brief Activate Belt motor
 * 
 */
void startBelt(){
	setOne(M6_di_PORT, PORT_M6_di);
}
/**
 * @brief Deactivate Belt motor
 * 
 */
void stopBelt(){
	setZero(M6_di_PORT, PORT_M6_di);
}
/**
 * @brief Public setup for Parte_3 library
 * 
 */
void setUpParte_3(void){
	setupBelt();
	setupLED_1();
	setUpSafeStop();
	setCallbackMsec(LED_1);
}
/**
 * @brief Public function for Parte_3 library
 * 
 */
void Parte_3(void){
	getNumberCar() > 0 ? startBelt() : stopBelt();
}
//////////////////////////////////////////////////////////
// Interruption handlers

ISR(INT0_vect){
	if(functionPointerStop != NULL) functionPointerStop();
}
