/*
 * General.c
 *
 * Created : 23/04/2023 18:20:57
 *  Author : Eduardo Palou de Comasema Juame
 *	version: 1.1.0
 */ 

#include "General.h"

// Variables globales
volatile uint32_t s = 0;
volatile uint32_t ms = 0;

// Funciones de trabajo
void (*functionPointerSec)();
void (*functionPointerMsec)();

//////////////////////////////
// Funciones de manejo de registros
uint8_t getBit(uint8_t reg, uint8_t bit){
	return reg & bit;
}
//////////////////////////////
// Funciones temporales 
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

int waitsec(uint32_t ds){
	uint32_t delaySec =  s;
	while(s < delaySec+ds){}
return 0;
}

int waitms(uint32_t dms){
	uint32_t init = ms;
	while( ms < init + dms ){
		dms++;
	}	
return 0;	
}

int getsec(void){
	return s;
}

int getms(void){
	return ms;
}

int setCallbackSec( void (*fptr)() ) {
	functionPointerSec = fptr;
return 0;
}

int setCallbackMsec( void (*fptr)() ) {
	functionPointerMsec = fptr;
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