/*
 * Parte_3.c
 *
 * Created: 23/04/2023 16:51:46
 * Author : Group 2 of Lavadero
 * Note: Alimentación no se conecta
 * version: 1.0.0
 */ 

#include "General.h"
#include "Parte_1.h"
#include "parte2.h"
#include "Parte_3.h"

int main(void)
{
	setUpGeneral();
	setUpParte_3();
	setUpParte_2();
	setUpParte_1();
	
    while (1) 
    {
		if(!getStop()){
			Parte_3();
			Parte_2();
			Parte_1();
		}
    }
return 0;
}

