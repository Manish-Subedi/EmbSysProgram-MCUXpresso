/*
===============================================================================
 Name        : main.c
 Author      : MANISH SUBEDI
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#if 1 //ex 1 starts here
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "ritimer_15xx.h"
#include "LpcUart.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"


int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    //Board_LED_Set(2, true);
#endif
#endif

    Chip_RIT_Init(LPC_RITIMER);

    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg_d = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };

	LpcUart dbgu(cfg_d);

	/* IO pins for lcd */
	DigitalIoPin rs(0, 8, false, false, false);
	DigitalIoPin en(1, 6, false, false, false);
	DigitalIoPin d4(1, 8, false, false, false);
	DigitalIoPin d5(0, 5, false, false, false);
	DigitalIoPin d6(0, 6, false, false, false);
	DigitalIoPin d7(0, 7, false, false, false);

	/* buttons configuration */
	DigitalIoPin B1(0, 17, true, true, true);
	DigitalIoPin B2(1, 11, true, true, true);
	DigitalIoPin B3(1, 9, true, true, true);

    // Force the counter to be placed into memory
    volatile static int i = 0;
    char buffer[40];
    const char status [2][5] { "UP", "DOWN"};

    //LCD object instantiation
    LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);

	// configure display geometry
	lcd.begin(16, 2);

    while(1) {
		lcd.setCursor(0, 0);
		sprintf(buffer, "%-6s%-6s%-4s","B1","B2","B3");
		lcd.print(buffer);

		lcd.setCursor(0, 1);
		sprintf(buffer+16, "%-6s%-6s%-4s", status[B1.read()], status[B2.read()], status[B3.read()]);
		lcd.print(buffer+16);

		/** testing the delayMicrosecond() **/
		/*
    	A0.write(true);
    	delayMicroseconds(55);

		A0.write(false);
		delayMicroseconds(35);

		A0.write(true);
		delayMicroseconds(40);

		A0.write(false);
		delayMicroseconds(20);


		char buf[100];
		if(i%10000==0){
			uint64_t val = (uint64_t) Chip_Clock_GetSystemClockRate() /1000000;
			snprintf(buf, 100, "clockrate: %ld compval: %lld counter: %lld\r\n", Chip_Clock_GetSystemClockRate(), val, Chip_RIT_GetCounter(LPC_RITIMER));
			dbgu.write(buf);
			}
		 */
		/* delayMicroseconds() test program ends */


		// Enter an infinite loop, just incrementing a counter
		i++;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
#endif //ex 1 ends here

#if 0 //ex 2 starts here
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#define TICKRATE_HZ (1000)

#include <cr_section_macros.h>
#include "ritimer_15xx.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include <string>
#include "RealtimeClock.h"

static RealTimeClock *rtc;
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Handle interrupt from SysTick timer
 * @return Nothing
 */
void SysTick_Handler(void)
{
	if(rtc != NULL) rtc->tick();
}
#ifdef __cplusplus
}
#endif

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    //Board_LED_Set(2, true);
#endif
#endif
    uint32_t sysTickRate;
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / TICKRATE_HZ);

    Chip_RIT_Init(LPC_RITIMER);

	time_t rawtime;
	time(&rawtime); // Polling the time
	tm * current_time = localtime(&rawtime);
	//RealTimeClock rt(current_time,TICKRATE_HZ);
	RealTimeClock rt(TICKRATE_HZ);

	rtc = &rt;
	tm timer;

	/* IO pins for lcd */
	DigitalIoPin rs(0, 8, false, false, false);
	DigitalIoPin en(1, 6, false, false, false);
	DigitalIoPin d4(1, 8, false, false, false);
	DigitalIoPin d5(0, 5, false, false, false);
	DigitalIoPin d6(0, 6, false, false, false);
	DigitalIoPin d7(0, 7, false, false, false);

	/* buttons configuration */
	DigitalIoPin B1(0, 17, true, true, true);
	DigitalIoPin B2(1, 11, true, true, true);
	DigitalIoPin B3(1, 9, true, true, true);

    // Force the counter to be placed into memory
    volatile static int i = 0;

    LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);
	// configure display geometry
	lcd.begin(16, 2);

	lcd.setCursor(0, 0);
	std::string str;

    while(1) {
    	rtc->getTime(&timer);
    	if(timer.tm_hour <= 9){
			str += ' ';
		}
		str.append(std::to_string(timer.tm_hour));
		str+=':';

		if(timer.tm_min <= 9){
			str += '0';
		}
		str.append(std::to_string(timer.tm_min));
		str+=':';

		if(timer.tm_sec <= 9){
			str += '0';
		}
		str.append(std::to_string(timer.tm_sec));

		lcd.print(str);
		str.clear();

		// Enter an infinite loop, just incrementing a counter
		i++;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
#endif //ex 2 ends here

#if 0 //ex 3 starts here
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "DigitalIoPin.h"
#include <string>
#include <atomic>
#include <stdio.h>

#define PININT_IRQ_HANDLER  PIN_INT0_IRQHandler	/* GPIO interrupt IRQ function name */
#define PININT_NVIC_NAME    PIN_INT0_IRQn	/* GPIO interrupt NVIC interrupt name */
#define PININT_INDEX   0	/* PININT index used for GPIO mapping */
#define TICKRATE_HZ1 (1000)

static volatile std::atomic_int counter;

// represents the times the button has been pressed
static volatile std::atomic_int value;

#ifdef __cplusplus
extern "C" {
#endif

void PIN_INT0_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));
	value++;
}

void SysTick_Handler(void)
{
	if(counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif

void Sleep(int ms){
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}

// This funciton sets up the sys tick
void Set_SysTickRate(int frequency){
	uint32_t sysTickRate;
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / frequency);
}

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
#endif

    Set_SysTickRate(TICKRATE_HZ1);

	std::atomic_int oldvalue = value;
	std::string str;

	/* Initialize PININT driver */
	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	DigitalIoPin sw1(0, 17, true, true, true);

	/* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PININT);

	/* Reset the PININT block */
	Chip_SYSCTL_PeriphReset(RESET_PININT);

	/* Map sw1 to pin interrupt 0*/
	Chip_INMUX_PinIntSel(PININT_INDEX, 0, 17);

	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));

	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(PININT_NVIC_NAME);
	NVIC_EnableIRQ(PININT_NVIC_NAME);

	while(1){
		Sleep(100);
		if(oldvalue != value){
			oldvalue = value;
			str.append("Button was pressed: ");
			str.append(std::to_string(value));
			str.append(" times\n\r");
			Board_UARTPutSTR(str.c_str());
			str.clear();
		}
	}
    return 0 ;
}
#endif

