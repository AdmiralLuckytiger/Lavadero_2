#include "Parte_2.h"

//LAVADERO VERTICAL
/* el setup en principio no hace nada(?)
 El lavado vertical comienza cuando el contador de SW1 sea 2 -> M2 ON
 El lavado vertical termina cuando se levanta la F_SO7 -> M2 OFF y se baja la bandera ----FIN----
*/

int setup_Lavado_vertical(){
	Flag_Contador = 0;
	final_lavadoV = 0;
	finLavadoV = 0;
	setZero(M2_en_PORT,PORT_M2_en);
	return 0;
}

int lavadoV(void){ //Lavado vertical empieza cuando contador de coche es mayor que 0 y bandera de final es menor que ese numero
	if ((getNumberCar() - final_lavadoV) > 0 )	setOne(M2_en_PORT,PORT_M2_en);
	else setZero(M2_en_PORT,PORT_M2_en);
	return 0;
}

int detectar_fin_coche_lavadoV(void){ //Con esta funcion detectamos si un coche ya ha salido del lavado vertical.
	//contador barrera
	if((getsec()>finLavadoV && finLavadoV != 0) && Flag_Contador == 0){ /**/
		final_lavadoV++;
		Flag_Contador = 1;
	}
	else if(Flag_Barrera && !PORT_SO2 && Flag_Contador == 1){ /**/
		Flag_Contador = 0;
	}
	return 0;
}
