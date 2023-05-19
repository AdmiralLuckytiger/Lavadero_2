/*
 * General.h
 *
 * 	Created : 23/04/2023 16:52:43
 *  Author : Eduardo Palou de Comasema Jaume - 18268
			 Damien Saga - 22442
 *	version: 1.1.2
 */ 

//	Librerias de trabajo
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
//	Construcci�n de libreria
#ifndef GENERAL_H_
#define GENERAL_H_

// Definici�n de macros de trabajo 
	#define setOne(Register,bit)  (Register |= bit )
	#define setZero(Register,bit) (Register &= ~bit)
// Redefinici�n de constantes 
	// Caracteristicas del microprocesador
		#define uCFreq 8000000
		#define delay_Barrera_Lavado_Vertical 1000
		#define pulsosBarrera 16
	// Estado de maqueta 
		#define CYCLE_WORKING 1
		#define CYCLE_STOPPED 0
	// Timer seconds => TIMER 1: Mode CTC (ICRn) with preescalar 256 
		#define TCCRSECA 0b00000000
		#define TCCRSECB 0b00001101
		#define TIMSKSEC 0b00000010
		#define ICRSEC   uCFreq/256
	// Timer miliseconds => TIMER 3: Mode CTC (ICRn) without preescalar 
		#define TCCRMSECA 0b00000000
		#define TCCRMSECB 0b00001001
		#define TIMSKMSEC 0b00000010
		#define ICRMSEC   uCFreq/1000
	// Motores 
		// Motor M1 => Barrera de entrada
			// Direction
		#define M1_di_PORT PORTL
		#define M1_di_DDR  DDRL
		#define M1_di_PIN  PINL
		
		#define PORT_M1_di (1 << PK0)
		#define DDR_M1_di  (1 << DDK0)
		#define PIN_M1_di  (1 << PINK0)
			// Enable
		#define M1_en_PORT PORTK
		#define M1_en_DDR  DDRK
		#define M1_en_PIN  PINK
		
		#define PORT_M1_en (1 << PK2)
		#define DDR_M1_en  (1 << DDK2)
		#define PIN_M1_en  (1 << PINK2)
		// Motor M2 => Rodillos verticales
			// Direction
		#define M2_di_PORT PORTK
		#define M2_di_DDR  DDRK
		#define M2_di_PIN  PINK
		
		#define PORT_M2_di (1 << PK4)
		#define DDR_M2_di  (1 << DDK4)
		#define PIN_M2_di  (1 << PINK4)
			// Enable
		#define M2_en_PORT PORTK
		#define M2_en_DDR  DDRK
		#define M2_en_PIN  PINK
		
		#define PORT_M2_en (1 << PK6)
		#define DDR_M2_en  (1 << DDK6)
		#define PIN_M2_en  (1 << PINK6)
		// Motor M3 => Rodillo horizontal altura
			// Direction => PCINT1
		#define M3_di_PORT PORTB
		#define M3_di_DDR  DDRB
		#define M3_di_PIN  PINB
		
		#define PORT_M3_di (1 << PB1)
		#define DDR_M3_di  (1 << DDB1)
		#define PIN_M3_di  (1 << PINB1)
			// Enable => PCINT3
		#define M3_en_PORT PORTB
		#define M3_en_DDR  DDRB
		#define M3_en_PIN  PINB
		
		#define PORT_M3_en (1 << PB3)
		#define DDR_M3_en  (1 << DDB3)
		#define PIN_M3_en  (1 << PINB3)	
		// Motor M4 => Rodillo horizontal giro
			// Direction
		#define M4_di_PORT PORTK
		#define M4_di_DDR  DDRK
		#define M4_di_PIN  PINK
		
		#define PORT_M4_di (1 << PK5)
		#define DDR_M4_di  (1 << DDK5)
		#define PIN_M4_di  (1 << PINK5)
			// Enable
		#define M4_en_PORT PORTK
		#define M4_en_DDR  DDRK
		#define M4_en_PIN  PINK

		#define PORT_M4_en (1 << PK7)
		#define DDR_M4_en  (1 << DDK7)
		#define PIN_M4_en  (1 << PINK7)
		// Motor M5 => Ventilador de secado
			// Direction
		#define M5_di_PORT PORTK
		#define M5_di_DDR  DDRK
		#define M5_di_PIN  PINK
		
		#define PORT_M5_di (1 << PK1)
		#define DDR_M5_di  (1 << DDK1)
		#define PIN_M5_di  (1 << PINK1)
			// Enable
		#define M5_en_PORT PORTK
		#define M5_en_DDR  DDRK
		#define M5_en_PIN  PINK

		#define PORT_M5_en (1 << PK3)
		#define DDR_M5_en  (1 << DDK3)
		#define PIN_M5_en  (1 << PINK3)
		// Motor M6 => Cinta de arrastre
			// Direction => PCINT5
		#define M6_di_PORT PORTB
		#define M6_di_DDR  DDRB
		#define M6_di_PIN  PINB

		#define PORT_M6_di (1 << PB5)
		#define DDR_M6_di  (1 << DDB5)
		#define PIN_M6_di  (1 << PINB5)
			// Enable => PCINT7
		#define M6_en_PORT PORTB
		#define M6_en_DDR  DDRB
		#define M6_en_PIN  PINB
		
		#define PORT_M6_en (1 << PB7)
		#define DDR_M6_en  (1 << DDB7)
		#define PIN_M6_en  (1 << PINB7)
	// Switches
		#define SW_PORT PORTD
		#define SW_DDR  DDRD
		#define SW_PIN  PIND
		// SW1 => INT3
		#define PORT_SW1 (1 << PD3)
		#define DDR_SW1  (1 << DDD3)
		#define PIN_SW1  (1 << PIND3)
		// SW2 => INT1
		#define PORT_SW2 (1 << PD1)
		#define DDR_SW2  (1 << DDD1)
		#define PIN_SW2  (1 << PIND1)
		// SW3 => INT2
		#define PORT_SW3 (1 << PD2)
		#define DDR_SW3  (1 << DDD2)
		#define PIN_SW3  (1 << PIND2)		
		// SW4 => INT0
		#define PORT_SW4 (1 << PD0)
		#define DDR_SW4  (1 << DDD0)
		#define PIN_SW4  (1 << PIND0)	
	// Leds
		#define LD_PORT PORTL
		#define LD_DDR  DDRL
		#define LD_PIN  PINL 
		// L1
		#define PORT_L1 (1 << PL1)
		#define DDR_L1  (1 << DDL1)
		#define PIN_L1  (1 << PINL1)
		// L2
		#define PORT_L4 (1 << PL3)
		#define DDR_L4  (1 << DDL3)
		#define PIN_L4  (1 << PINL3)		
		// L3
		#define PORT_L5 (1 << PL5)
		#define DDR_L5  (1 << DDL5)
		#define PIN_L5  (1 << PINL5)
		// L4
		#define PORT_L6 (1 << PL7)
		#define DDR_L6  (1 << DDL7)
		#define PIN_L6  (1 << PINL7)	
	// Sensores
		// REGISTROS S01-S05-S06-S12 B
		#define SOB_PORT PORTB
		#define SOB_DDR  DDRB
		#define SOB_PIN  PINB
		// REGISTROS S02-S03-S04-S010 L
		#define SOL_PORT PORTL
		#define SOL_DDR  DDRL
		#define SOL_PIN  PINL		
		// REGISTROS S07-S08-S09-S011 D
		#define SOD_PORT PORTD
		#define SOD_DDR  DDRD
		#define SOD_PIN  PIND		
		// SO1 => PCINT0
		#define PORT_SO1 (1 << PB0)
		#define DDR_SO1  (1 << DDB0)
		#define PIN_SO1  (1 << PINB0)		
		// SO2
		#define PORT_SO2 (1 << PL2)
		#define DDR_SO2  (1 << DDL2)
		#define PIN_SO2  (1 << PINL2)		
		// SO3
		#define PORT_SO3 (1 << PL4)
		#define DDR_SO3  (1 << DDL4)
		#define PIN_SO3  (1 << PINL4)
		// SO4
		#define PORT_SO4 (1 << PL6)
		#define DDR_SO4  (1 << DDL6)
		#define PIN_SO4  (1 << PINL6)
		// SO5 => PCINT6
		#define PORT_SO5 (1 << PB6)
		#define DDR_SO5  (1 << DDB6)
		#define PIN_SO5  (1 << PINB6)
		// SO6 => PCINT4
		#define PORT_SO6 (1 << PB4)
		#define DDR_SO6  (1 << DDB4)
		#define PIN_SO6  (1 << PINB4)
		// SO7
		#define PORT_SO7 (1 << PD4)
		#define DDR_SO7  (1 << DDD4)
		#define PIN_SO7  (1 << PIND4)
		// SO8
		#define PORT_SO8 (1 << PD6)
		#define DDR_SO8  (1 << DDD6)
		#define PIN_SO8  (1 << PIND6)
		// SO9
		#define PORT_SO9 (1 << PD7)
		#define DDR_SO9  (1 << DDD7)
		#define PIN_SO9  (1 << PIND7)
		// SO10
		#define PORT_SO10 (1 << PL0)
		#define DDR_SO10  (1 << DDL0)
		#define PIN_SO10  (1 << PINL0)
		// SO11
		#define PORT_SO11 (1 << PD5)
		#define DDR_SO11  (1 << DDD5)
		#define PIN_SO11  (1 << PIND5)
		// SO12 => PCINT2
		#define PORT_SO12 (1 << PB2)
		#define DDR_SO12  (1 << DDB2)
		#define PIN_SO12  (1 << PINB2)

// Prototipado de funciones comunes

	// Funciones de manejo de registros 
		uint8_t getBit(uint8_t,uint8_t);

	// Funciones temporales
		int setupTimers(void);
		int setCallbackSec( void (*fptr)() );
		int setCallbackMsec( void (*fptr)() );
		int setCallbackMsec_2( void (*fptr)() );
		int waitsec(uint32_t); 
		int waitms(uint32_t);
		uint32_t getsec(void);
		uint32_t getms(void);

	// Funciones de estado de Maqueta
		int getState(void); 
		int getNumberCar(void);

	// Funciones de interrupción
		int setUpInterrupts(void);

	// Funciones publicas
		int setUpGeneral(void);
		int stop(void);
		int getStop(void);
		char getFlagSO1(void);
		void setFlagSO1(int);
		int getPetition(void);
		void downPetiton(void);
		void incNumberCar(void);
#endif /* GENERAL_H_ */
