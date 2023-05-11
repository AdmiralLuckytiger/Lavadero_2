#include "Parte_2.h"



//BARRERA 
/*  El setup de la barrera debe comprobar que la barrera est� bajada y bajarla si no lo est� SO2
 La barrera se activa con una bandera de CHANGE STATE del sensor SO1 -> M1 ON y se baja la bandera
 comienza tambi�n el contador de pulsos del SW1, cuando sea 2 -> M1 OFF
 cuando se vuelva a alzar la bandera de SO1 por CHANGE -> M1 ON y se baja la bandera
 cuando SO2! y/o contador de SW1 sea 4 -> M1 OFF ----FIN----
*/

int setup_barrera(void){	
	Flag_Barrera = 0;
	cPulsos = 0;
	setFlagS01(0);
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
	return 0;
}


int barrera(void){
	//Flag_SO1 = !getBit(SOB_PIN,PIN_SO1);
	if(getFlagS01() && !Flag_Barrera && !stopBarrera){ //Si detecta un coche
		if(cPulsos < 2  && getFlagS01()){ // Subida de la barrera
			setOne(M1_en_PORT,PORT_M1_en);
		}
		else if(cPulsos >= 2 && getFlagS01()) { //Ha detectado dos pulsos. Barrera no se mueve y avanza el coche
			//mover_cinta();
			setZero(M1_en_PORT,PORT_M1_en);
			Flag_Barrera = 1;
			setFlagS01(0);			
		}
	}
	else if(!getFlagS01() && Flag_Barrera && !stopBarrera){ //La bandera está activa, por lo que baja la barrera. Se resetean las variables locales al alcanzar SO2
		setOne(M1_en_PORT,PORT_M1_en);
		if(!getBit(SOL_PIN,PIN_SO2)){
			Flag_Barrera = 0;
			cPulsos = 0;
			setZero(M1_en_PORT,PORT_M1_en);
			finBarrera=getsec();
			finLavadoV = 30 + finBarrera;	
			delayBarrera = 10 +finBarrera;
			stopBarrera = 1;	
		}		
	}

	if(getsec() >= delayBarrera && stopBarrera){
		stopBarrera = 0;
	}
	
return 0;
}

uint8_t getPulsos(void){
	return cPulsos;
}