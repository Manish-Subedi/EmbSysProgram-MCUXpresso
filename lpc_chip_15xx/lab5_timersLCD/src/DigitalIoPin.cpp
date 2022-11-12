/*
 * DigitalIOPin.cpp
 *
 *  Created on: 7 Sep 2022
 *      Author: Manish
 */

#include "chip.h"
#include "DigitalIoPin.h"
#include "board.h"

DigitalIoPin::DigitalIoPin(int port, int pin, bool input, bool pullup, bool invert):port(port),
																					pin(pin),
																					input(input),
																					pullup(pullup),
																					invert(invert)
{
	this->port = port;
	this->pin = pin;
	this->input = input;
	this->pullup = pullup;
	this->invert = invert;

	if(input == true && pullup == true && invert == true){
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
	}
	if(input == true && pullup == true && invert == false){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
		}
	if(input == false && pullup == false && invert == false){
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, IOCON_MODE_INACT | IOCON_DIGMODE_EN);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, port, pin);
	}
}

bool DigitalIoPin::read(){
	bool state = Chip_GPIO_GetPinState(LPC_GPIO, port, pin);
	return state;
}

void DigitalIoPin::write(bool state){
	Chip_GPIO_SetPinState(LPC_GPIO, port, pin, state);
}

DigitalIoPin::~DigitalIoPin() {}

