/*
 * Dice.cpp
 *
 *  Created on: 2 Sep 2022
 *      Author: Manish Subedi
 */

#include "chip.h"
#include "board.h"
#include "Dice.h"
#include "../../lab3_UART_morse/src/DigitalIoPin.h"

Dice::Dice() {
	PD1 = new DigitalIoPin(1, 9, false, false, false);
	PD2 = new DigitalIoPin(0, 29, false, false, false);
	PD3 = new DigitalIoPin(0, 9, false, false, false);
	PD4 = new DigitalIoPin(0, 10, false, false, false);
	PD5 = new DigitalIoPin(0, 16, false, false, false);
	PD6 = new DigitalIoPin(1, 3, false, false, false);
	PD7 = new DigitalIoPin(0, 0, false, false, false);

	PD7->write(false);
	PD1->write(false);
	PD6->write(false);
	PD5->write(false);
	PD3->write(false);
	PD2->write(false);
	PD4->write(false);
};
void Dice::Show(int number){
	switch(number){
		case 0:
			PD7->write(false);
			PD1->write(false);
			PD6->write(false);
			PD5->write(false);
			PD3->write(false);
			PD2->write(false);
			PD4->write(false);
			break;
		case 1:
			PD4->write(true);
			break;
		case 2:
			PD7->write(true);
			PD3->write(true);
			break;
		case 3:
			PD7->write(true);
			PD4->write(true);
			PD3->write(true);
			break;
		case 4:
			PD7->write(true);
			PD1->write(true);
			PD5->write(true);
			PD3->write(true);
			break;
		case 5:
			PD7->write(true);
			PD1->write(true);
			PD4->write(true);
			PD5->write(true);
			PD3->write(true);
			break;
		case 6:
			PD7->write(true);
			PD1->write(true);
			PD6->write(true);
			PD5->write(true);
			PD3->write(true);
			PD2->write(true);
			break;
		default:
			PD7->write(true);
			PD1->write(true);
			PD6->write(true);
			PD5->write(true);
			PD3->write(true);
			PD2->write(true);
			PD4->write(true);
			break;
	}
};

Dice::~Dice() {
	delete PD1;
	delete PD2;
	delete PD3;
	delete PD4;
	delete PD5;
	delete PD6;
	delete PD7;
};


