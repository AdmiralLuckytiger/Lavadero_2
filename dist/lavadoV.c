#include "Parte_2.h"

//LAVADERO VERTICAL
/* el setup en principio no hace nada(?)
 El lavado vertical comienza cuando el contador de SW1 sea 2 -> M2 ON
 El lavado vertical termina cuando se levanta la F_SO7 -> M2 OFF y se baja la bandera ----FIN----
*/

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
	if (getsec() >= finLavadoV && Flag_Contador){// Temporizador
		Flag_Contador=0;
		setZero(M2_en_PORT,PORT_M2_en);
		startLavadoV = 0;
	} else if(startLavadoV) { // No hay Temporizador
		setOne(M2_en_PORT,PORT_M2_en);
	}
	return 0;
}

