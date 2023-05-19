/*
 * Parte_3.c
 *
 * Created: 24/04/2023 18:42:29
 *  Author: Eduardo Palou de Comasema Jaume - 18268
			Damien Saga - 22442
 * version: 1.3.1
 */ 

#include "Parte_3.h"

//Variables Globales
void (*functionPointerStop)();
volatile uint8_t cycle_state_old = 0;
int old_state_SO10 = 1;
int old_state_SO11 = 1;
int finSemaforo = 0;
//Funciones de trabajo 

//////////////////////////////////////////////////////
// Parada de emergencia

/**
 * @brief Configure the routine for an emergency stop
 * 
 * @return int 
 */
int SafeStop(void) {
	stopBelt();
	parada_emergencia();
	parada2();
	stop();
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
	setOne(LD_DDR, DDR_L4); //Set the led 4 pin as an output
	setOne(LD_DDR, DDR_L5); //Set the led 5 pin as an output
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
		if((getms()/500)%2==0 ){ //If ms is a pair multiple of 500
			turnOnL1();
		}
		else if((getms()/500)%2==1){ //If ms is an impair multiple of 500
			turnOffL1();
		}
	}
	else if (cycle_state==CYCLE_STOPPED){
		if(cycle_state_old==CYCLE_WORKING){
			turnOffL1();
		}
		if((getms()%10000)==0){
			turnOnL1();
		}
		if((getms()%10500)==0){
			turnOffL1();
		}
	}
	cycle_state_old = cycle_state; 
}

/**
 * @brief Función para el control lógico del semaforo
 * 
 */
void LED_4_5(){
	// Evaluate and execute
	if(getBit(SOL_PIN, PIN_SO10) != old_state_SO10){ // Flanco
		if(getBit(SOL_PIN, PIN_SO10)) { // Flanco de subida
			setOne(LD_PORT, PORT_L4);
			setZero(LD_PORT, PORT_L5);
			finSemaforo = 0;
		}
	}
	
	if(getBit(SOD_PIN, PIN_SO11) != old_state_SO11){
		if(getBit(SOD_PIN, PIN_SO11)){
			setZero(LD_PORT, PORT_L4);
			finSemaforo = 1;
		}
	}

	if(getNumberCar() > 0 && finSemaforo){
		setOne(LD_PORT, PORT_L5);
	}

	// Update state Sensor
	old_state_SO11 = getBit(SOD_PIN, PIN_SO11);
	old_state_SO10 = getBit(SOD_PIN, PIN_SO10);
}
// Cinta de arrastre 
/**
 * @brief Setup the registers of the belt
 * 
 */
void setupBelt(){
	setOne(M6_di_DDR, DDR_M6_di); //Set the M6 direction pin as an output
	setOne(M6_en_DDR, DDR_M6_en); //Set the M6 en pin as an output
	setOne(M6_di_PORT, PORT_M6_di); //Set M6 rotation direction to right
}
/**
 * @brief Activate Belt motor
 * 
 */
void startBelt(){
	setOne(M6_en_PORT, PORT_M6_en);
}
/**
 * @brief Deactivate Belt motor
 * 
 */
void stopBelt(){
	setZero(M6_en_PORT, PORT_M6_en);
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
	//setCallbackMsec_2(LED_4_5);
}
/**
 * @brief Public function for Parte_3 library
 * 
 */
void Parte_3(void){
	LED_4_5();
	if(getNumberCar() > 0){
		if(!getBit(M6_en_PIN,PIN_M6_en))
			startBelt();
	}
	else{
		stopBelt();
	}
}
//////////////////////////////////////////////////////////
// Interruption handlers

ISR(INT0_vect){
	if(functionPointerStop != NULL) functionPointerStop();
}
