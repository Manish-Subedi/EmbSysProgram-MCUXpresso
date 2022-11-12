#if 0 //ex 1 starts

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include "LpcUart.h"

#define TICKRATE_HZ (1000)

#include <cr_section_macros.h>
#include "ritimer_15xx.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include <string>

#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include "DigitalIoPin.h"
#include "SleepMilli.h"

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

    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg_d = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };

	LpcUart dbgu(cfg_d);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

    // TODO: insert code here
    Chip_RIT_Init(LPC_RITIMER);
    //NVIC_EnableIRQ(RITIMER_IRQn);

	SleepMilli sleep;

    /* IO pins for lcd */
	DigitalIoPin rs(0, 8, false, false, false);
	DigitalIoPin en(1, 6, false, false, false);
	DigitalIoPin d4(1, 8, false, false, false);
	DigitalIoPin d5(0, 5, false, false, false);
	DigitalIoPin d6(0, 6, false, false, false);
	DigitalIoPin d7(0, 7, false, false, false);

	DigitalIoPin sw1(0, 17, true, true, true);
	DigitalIoPin sw2(1, 11, true, true, true);
	DigitalIoPin sw3(1, 9, true, true, true);

	dbgu.write("Hello World!\r\n");

    LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);

    lcd->begin(16,2);
    lcd->setCursor(0,0);

    SimpleMenu menu; /* this could also be allocated from the heap */

    IntegerEdit *time = new IntegerEdit(lcd, std::string("Time"), 0, 10);
    IntegerEdit *blank = new IntegerEdit(lcd, std::string("Blank"), 100, 200);
    IntegerEdit *light = new IntegerEdit(lcd, std::string("Light"), 0, 2);

    menu.addItem(new MenuItem(time));
    menu.addItem(new MenuItem(blank));
    menu.addItem(new MenuItem(light));

    int t_count = 0;

    menu.event(MenuItem::show);

	while(1){
		char buffer[100];

		if(sw1.read()){
			while(sw1.read());
			menu.event(MenuItem::up);
			snprintf(buffer, 100, "\nTime(0-10): %d\r\nBlank(0-100): %d\r\nLight(0-2): %d\r\n", time->getValue(), blank->getValue(), light->getValue());
			dbgu.write(buffer);
			t_count = 0;
		}
		if(sw2.read()){
			while(sw2.read());
			menu.event(MenuItem::ok);
			snprintf(buffer, 100, "\nTime(0-10): %d\r\nBlank(0-100): %d\r\nLight(0-2): %d\r\n", time->getValue(), blank->getValue(), light->getValue());
			dbgu.write(buffer);
			t_count = 0;
		}
		if(sw3.read()){
			while(sw3.read());
			menu.event(MenuItem::down);
			snprintf(buffer, 100, "\nTime(0-10): %d\r\nBlank(0-100): %d\r\nLight(0-2): %d\r\n", time->getValue(), blank->getValue(), light->getValue());
			dbgu.write(buffer);
			t_count = 0;
		}

		if(t_count == 100){
			menu.event(MenuItem::back);
			snprintf(buffer, 100, "Going back");
			dbgu.write(buffer);
		}
		sleep.Sleep(100);
		t_count += 1;
	}
	return 0;
}
#endif

#if 0 //ex 3 starts

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include "LpcUart.h"

#define TICKRATE_HZ (1000)

#include <cr_section_macros.h>
#include "ritimer_15xx.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include <string>

#include "SimpleMenu.h"
#include "SleepEdit.h"
#include "IntegerEdit.h"
#include "KillerEdit.h"
#include "DigitalIoPin.h"

#include "SleepMilli.h"

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
    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg_d = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };

	LpcUart dbgu(cfg_d);

    /* check watchdog status flag */
	uint32_t wdStatus = Chip_WWDT_GetStatus(LPC_WWDT);
	if(wdStatus) Board_LED_Set(0, true); //set red led if reset caused by watchdog
	else Board_LED_Set(1, true); //else green led

    uint32_t wdtFreq;
    /* Enable the WDT oscillator */
    Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_WDTOSC_PD);

    /* The WDT divides the input frequency into it by 4 */
    wdtFreq = Chip_Clock_GetWDTOSCRate() / 4;

    /* Initialize WWDT (also enables WWDT clock) */
    Chip_WWDT_Init(LPC_WWDT);

    /* Set watchdog feed time constant to approximately 2s */
    Chip_WWDT_SetTimeOut(LPC_WWDT, wdtFreq * 5);

	/* Configure WWDT to reset on timeout */
	Chip_WWDT_SetOption(LPC_WWDT, WWDT_WDMOD_WDRESET);

	/* Start watchdog */
	Chip_WWDT_Start(LPC_WWDT);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

    // TODO: insert code here
    Chip_RIT_Init(LPC_RITIMER);
    //NVIC_EnableIRQ(RITIMER_IRQn);

	SleepMilli sleep;

    /* IO pins for lcd */
	DigitalIoPin rs(0, 8, false, false, false);
	DigitalIoPin en(1, 6, false, false, false);
	DigitalIoPin d4(1, 8, false, false, false);
	DigitalIoPin d5(0, 5, false, false, false);
	DigitalIoPin d6(0, 6, false, false, false);
	DigitalIoPin d7(0, 7, false, false, false);

	DigitalIoPin sw1(0, 17, true, true, true);
	DigitalIoPin sw2(1, 11, true, true, true);
	DigitalIoPin sw3(1, 9, true, true, true);

	dbgu.write("Hello World!\r\n");

    LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);

    lcd->begin(16,2);
    lcd->setCursor(0,0);

    SimpleMenu menu; /* this could also be allocated from the heap */
#if 0 //SleepEdit objects
    SleepEdit *time = new SleepEdit(lcd, std::string("Time"), 0, 10);
    SleepEdit *blank = new SleepEdit(lcd, std::string("Blank"), 100, 200);
    SleepEdit *light = new SleepEdit(lcd, std::string("Light"), 0, 2);
#endif
#if 1 //killerEdit objects
    KillerEdit *time = new KillerEdit(lcd, std::string("Time"), 0, 10);
	KillerEdit *blank = new KillerEdit(lcd, std::string("Blank"), 100, 200);
	KillerEdit *light = new KillerEdit(lcd, std::string("Light"), 0, 2);
#endif
    menu.addItem(new MenuItem(time));
    menu.addItem(new MenuItem(blank));
    menu.addItem(new MenuItem(light));

    int t_count = 0;

    menu.event(MenuItem::show);

	while(1){
		char buffer[100];

		if(sw1.read()){
			while(sw1.read());
			menu.event(MenuItem::up);
			snprintf(buffer, 100, "\nTime(0-10): %d\r\nBlank(0-100): %d\r\nLight(0-2): %d\r\n", time->getValue(), blank->getValue(), light->getValue());
			dbgu.write(buffer);
			t_count = 0;
		}
		if(sw2.read()){
			while(sw2.read());
			menu.event(MenuItem::ok);
			snprintf(buffer, 100, "\nTime(0-10): %d\r\nBlank(0-100): %d\r\nLight(0-2): %d\r\n", time->getValue(), blank->getValue(), light->getValue());
			dbgu.write(buffer);
			t_count = 0;
		}
		if(sw3.read()){
			while(sw3.read());
			menu.event(MenuItem::down);
			snprintf(buffer, 100, "\nTime(0-10): %d\r\nBlank(0-100): %d\r\nLight(0-2): %d\r\n", time->getValue(), blank->getValue(), light->getValue());
			dbgu.write(buffer);
			t_count = 0;
		}

		if(t_count == 100){
			menu.event(MenuItem::back);
			snprintf(buffer, 100, "Returning back");
			dbgu.write(buffer);
		}
		sleep.Sleep(100);
		t_count += 1;

		/* feed the WatchDog timer */
		Chip_WWDT_Feed(LPC_WWDT);
	}
	return 0;
}
#endif
