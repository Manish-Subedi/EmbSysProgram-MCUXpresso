/*
 * Dice.h
 *
 *  Created on: 2 Sep 2022
 *      Author: Manish
 */

#ifndef DICE_H_
#define DICE_H_

#include "board.h"
#include "../../lab3_UART_morse/src/DigitalIoPin.h"

class Dice {
	public:
		Dice();
		virtual ~Dice();
		void Show(int number);
	private:
		DigitalIoPin *PD1;
		DigitalIoPin *PD2;
		DigitalIoPin *PD3;
		DigitalIoPin *PD4;
		DigitalIoPin *PD5;
		DigitalIoPin *PD6;
		DigitalIoPin *PD7;

};

#endif /* DICE_H_ */
