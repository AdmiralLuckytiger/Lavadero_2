/*
 * General.c
 *
 * 	Created : 23/04/2023 18:20:57
 *  Author : Eduardo Palou de Comasema Jaume - 18268
			Damien Saga - 22442
 *	version: 1.5.2
 *	note: previous optimization &&
 */ 

#include "General.h"

// Variables globales
volatile uint32_t s = 0;
volatile uint32_t ms = 0;
volatile uint8_t numCar = 0;
volatile uint8_t Stop = 0;
volatile char Flag_SO1 = 0; // 0 (No flanco) 1 (Flanco)
volatile uint8_t old_state_SO12 = 1;
volatile uint8_t old_state_SO1 = 1;
volatile uint8_t petition = 0;

// Funciones de trabajo
void (*functionPointerSec)();
void (*functionPointerMsec)();
void (*functionPointerMsec_2)();

//////////////////////////////
// Funciones de manejo de registros
/**
 * @brief Get the Bit object
 * 
 * @param reg 
 * @param bit 
 * @return uint8_t 
 */
uint8_t getBit(uint8_t reg, uint8_t bit){
	return (reg & bit) > 0 ? 1 : 0;
}
//////////////////////////////
// Funciones temporales 
/**
 * @brief Setup the registers of timer 1 and 3 for s and ms counter
 * 
 * @return int 
 */
int setupTimers(void){
	cli();
	// Timer ms
	TCCR1A = TCCRSECA;
	TCCR1B = TCCRSECB;
	TIMSK1 = TIMSKSEC;
	OCR1A = ICRSEC;
	// Timer s
	TCCR3A = TCCRMSECA;
	TCCR3B = TCCRMSECB;
	TIMSK3 = TIMSKMSEC;
	OCR3A = ICRMSEC;
	sei();
return 0;	
}
/**
 * @brief Blocks the flow of code ds seconds with a resolution of 1 second
 * 
 * @param ds 
 * @return int 
 */
int waitsec(uint32_t ds){
	volatile uint32_t delay = s + ds;
	while( s < delay ){}
return 0;
}
/**
 * @brief Blocks the flow of code ms miliseconds with a resolution of 1 milisecond
 * 
 * @param dms 
 * @return int 
 */
int waitms(uint32_t dms){
	volatile uint32_t delay = ms + dms;
	while( ms < delay ){}	
return 0;	
}
/**
 * @brief Returns the value of seconds past since the code starts
 * 
 * @return int 
 */
uint32_t getsec(void){
	return s;
}
/**
 * @brief Returns the value of miliseconds past since the code starts
 * 
 * @return int 
 */
uint32_t getms(void){
	return ms;
}
/**
 * @brief Set the Callback Sec object
 * 
 * @param fptr 
 * @return int 
 */
int setCallbackSec( void (*fptr)() ) {
	functionPointerSec = fptr;
return 0;
}
/**
 * @brief Set the Callback Msec function
 * 
 * @param fptr 
 * @return int 
 */
int setCallbackMsec( void (*fptr)() ) {
	functionPointerMsec = fptr;
return 0;
}

/**
 * @brief Set an additional Callback Msec function
 * 
 * @param fptr 
 * @return int 
 */
int setCallbackMsec_2( void (*fptr)() ) {
	functionPointerMsec_2 = fptr;
return 0;
}

/**
 * @brief Get if the facility is working
 * 
 * @return int 
 */
int getState(void) {
	return getBit(M6_en_PIN, PIN_M6_en) > 0 ? CYCLE_WORKING : CYCLE_STOPPED ;
}

/**
 * @brief Return the number of cars in the carwhaser
 * 
 */
int getNumberCar(){
	return numCar;
} 

/**
 * @brief Set PCInt interruption registers
 * 
 * @return int 
 */
int setUpInterrupts(){
	PCMSK0 |= 0b00000101;
	PCICR  |= 0b00000001;
return 0;
}

// Public interface for General library
/**
 * @brief Set the Up configuration of timers and interruptions
 * 
 * @return int 
 */
int setUpGeneral(){
	setUpInterrupts();
	setupTimers();
return 0;
}

/**
 * @brief Set flag to stop the machine
 * 
 * @return int 
 */
int stop(){
	Stop = 1;
}

/**
 * @brief Return the value of flag stop
 * 
 * @return int 
 */
int getStop(){
	return Stop;
}

/**
 * @brief Get state of FlagSO1
 * 
 * @return char 
 */
char getFlagSO1(){
	return Flag_SO1;
}

/**
 * @brief Set the Flag SO1 
 * 
 * @param valor 
 */
void setFlagSO1(int valor){
	Flag_SO1 = valor;
}

/**
 * @brief Set down the flag petition
 * 
 */
void downPetiton(void){
	petition = 0;
}

/**
 * @brief Get the Petition state
 * 
 * @return int 
 */
int getPetition(void){
	return petition;
}

/**
 * @brief Increments the number of cars in the facility
 * 
 */
void incNumberCar(void){
	numCar++;
}

////////////////////////////
// Interrupts handlers
ISR(TIMER1_COMPA_vect){
	s++;
	if (functionPointerSec != NULL) functionPointerSec();
}

ISR(TIMER3_COMPA_vect){
	ms++;
	if (functionPointerMsec != NULL) functionPointerMsec();
	//if (functionPointerMsec_2 != NULL) functionPointerMsec_2();
}

ISR(PCINT0_vect){
	// interrupci�n activada por SO1
	if(getBit(SOB_PIN,PIN_SO1) != old_state_SO1){
		if(!getBit(SOB_PIN,PIN_SO1)) petition = 1;
		Flag_SO1 = !Flag_SO1;
	}
	// Interrupci�n activada por SO1
	if(getBit(SOB_PIN,PIN_SO12) != old_state_SO12){
		if(!getBit(SOB_PIN,PIN_SO12) && !getBit(SOD_PIN,PIN_SO11) ){
			if(numCar > 0 ){
				numCar--;
			}
		}
	}
	old_state_SO12 = getBit(SOB_PIN,PIN_SO12);
	old_state_SO1 =  getBit(SOB_PIN,PIN_SO1);
}

