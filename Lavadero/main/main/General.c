/*
 * General.c
 *
 * Created : 23/04/2023 18:20:57
 *  Author : Eduardo Palou de Comasema Juame
 *	version: 1.1.1
 *	note: previous optimization
 */ 

#include "General.h"

// Variables globales
volatile uint32_t s = 0;
volatile uint32_t ms = 0;
uint8_t numCar = 0;

// Funciones de trabajo
void (*functionPointerSec)();
void (*functionPointerMsec)();

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
	return reg & bit;
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
int getsec(void){
	return s;
}
/**
 * @brief Returns the value of miliseconds past since the code starts
 * 
 * @return int 
 */
int getms(void){
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
 * @brief Set the Callback Msec object
 * 
 * @param fptr 
 * @return int 
 */
int setCallbackMsec( void (*fptr)() ) {
	functionPointerMsec = fptr;
return 0;
}
/**
 * @brief Get if any motor is on
 * 
 * @return int 
 */
int getState(void) {
	uint8_t acc = 0; 
	acc += getBit(M1_en_PIN, PIN_M1_en);
	acc += getBit(M2_en_PIN, PIN_M2_en);
	acc += getBit(M3_en_PIN, PIN_M3_en);
	acc += getBit(M4_en_PIN, PIN_M4_en);
	acc += getBit(M5_en_PIN, PIN_M5_en);
	acc += getBit(M6_en_PIN, PIN_M6_en);
	return acc > 0 ? CYCLE_WORKING : CYCLE_STOPPED ;
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

////////////////////////////
// Interrupts handlers
ISR(TIMER1_COMPA_vect){
	s++;
	if (functionPointerSec != NULL) functionPointerSec();
}

ISR(TIMER3_COMPA_vect){
	ms++;
	if (functionPointerMsec != NULL) functionPointerMsec();
}

ISR(PCINT0_vect){
	if(getBit(SOB_PIN,PIN_SO1)) numCar++;
}

ISR(PCINT2_vect){
	if(getBit(SOB_PIN,PIN_SO12)) numCar--;
}