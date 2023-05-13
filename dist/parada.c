#include "parte2.h"


//parar todos los motores

int parada2(void){
	setZero(M1_en_PORT,PORT_M1_en);
	setZero(M2_en_PORT,PORT_M2_en);
	return 0;
}