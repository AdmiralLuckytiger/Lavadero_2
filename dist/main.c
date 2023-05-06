/*
 * Parte_3.c
 *
 * Created: 23/04/2023 16:51:46
 * Author : Group 2 of Lavadero
 */ 

#include "General.h"
#include "Parte_1.h"
#include "Parte_3.h"

int main(void)
{
	setUpParte_3();
	//setUpParte_2();
	setUpParte_1();
    while (1) 
    {
		Parte_3();
		//Parte_2()
		Parte_1();
    }
return 0;
}

