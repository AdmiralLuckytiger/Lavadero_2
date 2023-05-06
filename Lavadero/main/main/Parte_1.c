#include "Parte_1.h"

void Horizontal_Setup()
{
	cli();

	DDRL=0b00000000; 
	DDRD=0b00000000; 
	DDRB=0b00001010; 
	DDRK=0b10001010;

	TCCR5A = 0x00;
	TCCR5B = 0x0C;
	OCR5A  = 3124;
	TIMSK5 = 0x02;


	EICRA= 0b00000011; //(tick) INT3:0 incluyen  PD1 Y PD2 y es asíncrona (?) 0x11 habilita solo flancos de subida
	//EIMSK= 0b00000110;  //(tick) Enable sólo de PD1 Y PD2 bits

	sei();
}

void Horizontal_Limpiar()
{
	if(estado_sensores[3]== 1 || estado_sensores[5]==1)
	{
		PORT_M3= UP_M3; // sube para evitar la colision
	}

	else
	{

		if(estado_sensores[3]==0 && estado_sensores[4]==0 && estado_sensores[5]==0)
		{
			sucio=0;
		}

		PORT_M3= OFF_M3;
	}

}

void Horizontal_Sucio() //Por defecto se encuentra en el fin de carrera inferior
{
	//Fase rodillo horizontal
	if(sucio==1 || estado_sensores[3]==1 || estado_sensores[4]==1 || estado_sensores[5]==1 )
	{
		sucio=1;
		PORT_M4=ON_M4;
		Horizontal_Limpiar();
	}
	else
	{
		PORT_M3= DOWN_M3;
		PORT_M4=OFF_M4;
	}
}
void Horizontal_Secar()
{

	if(estado_sensores[7]== 1 || estado_sensores[9]==1)
	{
		PORT_M5= UP_M5; // sube para evitar la colision
	}

	else
	{

		if(estado_sensores[7]==0 && estado_sensores[8]==0 && estado_sensores[9]==0)
		{
			humedo=0;
		}

		PORT_M5= OFF_M5;
	}

}

void Horizontal_Humedo() //Por defecto se encuentra en el fin de carrera inferior
{
	//Fase rodillo horizontal
	if(humedo==1 || estado_sensores[7]==1 || estado_sensores[8]==1 || estado_sensores[9]==1 )
	{
		humedo=1;
		Horizontal_Secar();
	}
	else
	{
		PORT_M5= DOWN_M5;
	}
}

void parada_emergencia(){
	PORT_M3=OFF_M3;
	PORT_M4=OFF_M4;
	PORT_M5=OFF_M5;
}

void reset_rodillos(){
	PORT_M3=DOWN_M3;
	PORT_M5=DOWN_M5;
}

///////////////////////////////////////////
// Interrupt handlers
ISR(TIMER5_COMPA_vect)  //interrupción para los fines de carrera SW2
{
	if((PIN_SO3&0b00010000)!=0b00010000) estado_sensores[3]= 1;

	else estado_sensores[3]= 0;

	if((PIN_SO4&0b01000000)!=0b01000000) estado_sensores[4]= 1;

	else estado_sensores[4]= 0;

	if((PIN_SO5&0b01000000)!=0b01000000) estado_sensores[5]= 1;

	else estado_sensores[5]= 0;

	if((PIN_SO7&0b00010000)!=0b00010000) estado_sensores[7]= 1;

	else estado_sensores[7]= 0;

	if((PIN_SO8&0b01000000)!=0b01000000) estado_sensores[8]= 1;

	else estado_sensores[8]= 0;

	if((PIN_SO9&0b10000000)!=0b10000000) estado_sensores[9]= 1;

	else estado_sensores[9]= 0;

}

ISR(INT1_vect) //interrupción para los fines de carrera SW2
{
	//if(PORT_M3 != UP_M3)	
	//{
		//PORT_M3=OFF_M3;
		//PORT_M4=OFF_M4;
	//}
}

ISR(INT2_vect) //interrupción para los fines de carrera SW3
{
	//if(PORT_M5 != UP_M5)
	//{
		//PORT_M5=OFF_M5;
	//}
}

int setUpParte_1(void){
	Horizontal_Setup();
return 0;
}

int Parte_1(void){
	Horizontal_Sucio();
	Horizontal_Humedo();
return 0;
}