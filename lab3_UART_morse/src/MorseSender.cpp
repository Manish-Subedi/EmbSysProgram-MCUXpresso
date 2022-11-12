/*
 * morseSender.cpp
 *
 *  Created on: 14 Sep 2022
 *      Author: Manish
 */

#include "MorseSender.h"
#include "DigitalIoPin.h"
#include <atomic>
#include "chip.h"
#include <ctype.h>
#include <String>

static volatile std::atomic_int counter;
#ifdef __cplusplus
extern "C" {
#endif
/*
* @brief Handle interrupt from SysTick timer
* @return Nothing
*/

void SysTick_Handler(void)
{
if(counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif
void Sleep(int ms)
{
counter = ms;
while(counter > 0) {
__WFI();
}
}

MorseSender::MorseSender(DigitalIoPin *red, DigitalIoPin *a0): red(red), a0(a0) {}


void MorseSender::sendMorse(const char *str, int dot_len){
	for(int i = 0; str[i] != 0; i++) {
			sendMorse((str[i]), dot_len);
		}
};

void MorseSender::sendMorse(char c, int dot_len){
	if(isspace(c)){
		a0->write(false);
		//inter word gap
		Sleep(3 * dot_len);
	}
	else if(isalpha(c) || isdigit(c)){
		c = toupper(c);
		for(int k=0; ITU_morse[k].symbol != 0; k++){
			if(c == ITU_morse[k].symbol){
				for(int m=0; ITU_morse[k].code[m] != 0; m++){
					a0->write(true);
					red->write(false);
					Sleep(ITU_morse[k].code[m] * dot_len);
					a0->write(false);
					red->write(true);
					//inter-element gap
					Sleep(1 * dot_len);

				}
				break; //breaks the for loop
			}
		}
	}
	else{
		c = 'X';
		int in_X = 23; //index of X
		for(int m=0; ITU_morse[in_X].code[m] != 0; m++){
			red->write(true);
			a0->write(true);
			Sleep(ITU_morse[in_X].code[m] * dot_len);
			red->write(false);
			a0->write(false);
			//inter-element gap
			Sleep(1 * dot_len);
		}
	}
	//inter letter gap
	Sleep(2 * dot_len);
};

MorseSender::~MorseSender() {
	delete a0;
	delete red;
};

