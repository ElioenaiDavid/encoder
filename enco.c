/*
 * enco.c
 *
 *  Created on: 9 nov. 2019
 *      Author: David
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "enco.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#define B 100
#define A 20
int PinA,PinB,giro=50;
int pinA = 3; // Connected to CLK on KY-040
int pinB = 4; // Connected to DT on KY-040
int encoderPosCount = 0;
int pinALast;
int aVal,ver;
bool bCW;
int fc;
int pasos;
void encoinit(void){

	SIM->SCGC5 |= 0x800; /* enable clock to Port B */
	PORTC->PCR[8] = 0x100; /* make PTB19 pin as GPIO */
	PTC->PDDR &= ~0x100; /* make PTB19 as output pin */
	SIM->SCGC5 |= 0x200; /* enable clock to Port A */
	PORTA->PCR[5] = 0x100; /* make PTA1 pin as GPIO and enable pull-up */
	PTA->PDDR &= ~0x020; /* make PTA1 as input pin */
	SIM->SCGC5 |= 0x400; /* enable clock to Port B */
		PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO */
		PORTB->PCR[18] = 0x100;
		PTB->PDDR |= 0xC0000;
}
int direction (void){

	aVal = (PTA->PDIR & 0x20);
		 if (aVal != pinALast){ // Means the knob is rotating
		 // if the knob is rotating, we need to determine direction
		 // We do that by reading pin B.
			 ver = (PTC->PDIR & 0x100);
		 if ((PTC->PDIR & 0x100) != (aVal*8)) { // Means pin A Changed first - We're Rotating Clockwise.
		 encoderPosCount ++;
		 bCW = true;
		PTB->PSOR = 0x80000;
		PTB->PCOR = 0x40000;
		fc=1;
		 } else {// Otherwise B changed first and we're moving CCW
		 bCW = false;

		 encoderPosCount--;
			PTB->PCOR = 0x80000;
			PTB->PSOR = 0x40000;
			fc=2;
		 }

		 }
		 pinALast = aVal;
		 return fc;
}
int steps(int p){
	pasos =0;
	for (int t=0;t<p;t++){
	aVal = (PTA->PDIR & 0x20);
			 if (aVal != pinALast){ // Means the knob is rotating
			 // if the knob is rotating, we need to determine direction
			 // We do that by reading pin B.
				 ver = (PTC->PDIR & 0x100);
			 if ((PTC->PDIR & 0x100) != (aVal*8)) { // Means pin A Changed first - We're Rotating Clockwise.
				 pasos++;


			 } else {// Otherwise B changed first and we're moving CCW
			 bCW = false;

			 pasos--;

			 }

			 }
			 pinALast = aVal;
			 delayMs(1);
	}
	return pasos;
}
void delayMs(int n) {
		int i;
		int j;
		for(i = 0 ; i < n; i++)
			for (j = 0; j < 7000; j++) {}
	}
