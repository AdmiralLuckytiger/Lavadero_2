#include <avr/io.h>
#include <avr/interrupt.h>
#include "General.h"

#ifndef PARTE_1_H_
#define PARTE_1_H_

#define PIN_SW2 PIND
#define PIN_SW3 PIND

#define PORT_SW2 PORTD
#define PORT_SW3 PORTD

#define PORT_SO3 PORTL
#define PORT_SO4 PORTL
#define PORT_SO5 PORTB
//#define PORT_SO6 PORTK

#define PORT_SO7 PORTD
#define PORT_SO8 PORTD
#define PORT_SO9 PORTD

#define PORT_M3 PORTB
#define PORT_M4 PORTK
#define PORT_M5 PORTK

#define PIN_SO3 PINL
#define PIN_SO4 PINL

#define PIN_SO5 PINB
//#define PIN_SO6 PINB

#define PIN_SO7 PIND
#define PIN_SO8 PIND
#define PIN_SO9 PIND

#define PIN_M3 PINB
#define PIN_M4 PINK
#define PIN_M5 PINK

#define TOCA   0
#define NOTOCA 1



#define OFF_M3     (PIN_M3&0b11110111)
#define UP_M3      (PIN_M3|0b00001010)
#define DOWN_M3    ((0b00001000|(PIN_M3&0b11111101)))

#define OFF_M4  (PIN_M4&0b01111111)
#define ON_M4 (PIN_M4|0b10000000)

#define OFF_M5     (PIN_M5&0b11110111)
#define UP_M5      (PIN_M5|0b00001010)
#define DOWN_M5    ((0b00001000|(PIN_M5&0b11111101)))


#define VECT_SW2 INT1_vect
#define VECT_SW3 INT2_vect


int sucio=0;
int humedo=0;
int  estado_sensores[12]={0,0,0,0,0,0,0,0,0,0,0,0}; // hay doce sensores en el tunel de lavado (los nuestros van del 3 al 9);

void parada_emergencia();

void reset_rodillos();

// Interfaz publica
void setUpParte_1(void);
void Parte_1(void);

#endif /* PARTE_1_H_ */