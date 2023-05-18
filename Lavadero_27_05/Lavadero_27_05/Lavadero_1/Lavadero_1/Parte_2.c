/*
 * General.c
 *
 * 	Created : 23/04/2023 18:20:57
 *  Author : Jorge Martínez de la Mata Gaitán - 18211
			Eduardo Palou de Comasema Jaume - 18268
 *	version: 1.8.1
 *	note:
 */ 


#include "Parte_2.h"

//////////////////////////////////////////////////////////
// Funciones Barrera

/**
 * @brief Inicialización registros y variables asociados a la barrera.
 * 
 * @return int 
 */
int setup_barrera(void){	
	Flag_Barrera = 0;
	cPulsos = 0;
	startLavadoV = 0;
	setFlagSO1(0);
	stopBarrera = 0;
	finBarrera = 0;
		//setup puerto de salida el motor 1 --Bit del M1 como salida
		setOne(M1_en_DDR,DDR_M1_en);
		//setup puerto de salida el motor 2 --Bit del M2 como salida
		setOne(M2_en_DDR,DDR_M2_en);
		//setup por determinar - Bit de luz como salida getCoche
		setOne(LD_DDR, DDR_L1);
		//setup puerto de entrada SO1 Bit
		setZero(SOB_DDR,DDR_SO1);
		//setup puerto de entrada SO2 Bit
		setZero(SOL_DDR,DDR_SO2);
		//setup puerto de entrada SW1 Bit
		setZero(SW_DDR,DDR_SW1);	
	while(getBit(SOL_PIN,PIN_SO2)){
		setOne(M1_en_PORT,PORT_M1_en);
		} //Activamos la barrera hasta que se detecte que el SW2 se active
	setZero(M1_en_PORT,PORT_M1_en);
	cPulsos = 0;
	return 0;
}

/**
 * @brief Control logico asociado a la barrera.
 * 
 * @return int 
 */
int barrera(void){
	//Flag_SO1 = !getBit(SOB_PIN,PIN_SO1);
	if(getFlagSO1() && !Flag_Barrera && !stopBarrera){ //Si detecta un coche
		if(cPulsos < pulsosBarrera  && getFlagSO1()){ // Subida de la barrera
			setOne(M1_en_PORT,PORT_M1_en);
			startLavadoV = 1;
		}
		else if(cPulsos >= pulsosBarrera && getFlagSO1()) { //Ha detectado dos pulsos. Barrera no se mueve y avanza el coche
			//mover_cinta();
			setZero(M1_en_PORT,PORT_M1_en);
			Flag_Barrera = 1;
			incNumberCar();
			downPetiton();	
		}
	}
	else if(!getFlagSO1() && Flag_Barrera && !stopBarrera){ //La bandera está activa, por lo que baja la barrera. Se resetean las variables locales al alcanzar SO2
		setOne(M1_en_PORT,PORT_M1_en);
		if(!getBit(SOL_PIN,PIN_SO2)){
			Flag_Barrera = 0;
			cPulsos = 0;
			setZero(M1_en_PORT,PORT_M1_en);
			finBarrera=getms();
			finLavadoV = delay_Barrera_Lavado_Vertical + finBarrera;	
			delayBarrera = delay_Barrera_Lavado_Vertical + finBarrera;
			stopBarrera = 1;
			Flag_Contador = 1;	
		}		
	}

	if(getms() >= delayBarrera && stopBarrera){
		stopBarrera = 0;
	}
	
return 0;
}

//////////////////////////////////////////////////////////
// Lavado Vertical

/**
 * @brief Inicialización registros lavado vertical
 * 
 * @return int 
 */
int setup_Lavado_vertical(){
	Flag_Contador = 0;
	final_lavadoV = 0;
	finLavadoV = 0;
	setZero(M2_en_PORT,PORT_M2_en);
	return 0;
}

/**
 * @brief Control de funcionamiento de lavado
 * 
 * @return int 
 */
int lavadoV(void){ 
	if (getms() >= finLavadoV && Flag_Contador){// Temporizador
		Flag_Contador=0;
		setZero(M2_en_PORT,PORT_M2_en);
		startLavadoV = 0;
	} else if(startLavadoV) { // No hay Temporizador
		setOne(M2_en_PORT,PORT_M2_en);
	}
	return 0;
}

//////////////////////////////////////////////////////////
// Interfaz Publica de la parte

/**
 * @brief Get the Pulsos value
 * 
 * @return uint8_t 
 */
uint8_t getPulsos(void){
	return cPulsos;
}

/**
 * @brief Interfaz publica para configuración Parte_2
 * 
 * @return int 
 */
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

/**
 * @brief Interfaz publica para control lógico Parte_2
 * 
 * @return int 
 */
int Parte_2(void){
	barrera();
	lavadoV();
	return 0;
}

/**
 * @brief Desactiva los motores asociados a la parte 2
 * 
 * @return int 
 */
int parada2(void){
	setZero(M1_en_PORT,PORT_M1_en);
	setZero(M2_en_PORT,PORT_M2_en);
	return 0;
}

///////////////////////////////////////////////////////
// Interrupt handlers
ISR(INT3_vect){
	cPulsos++;
}