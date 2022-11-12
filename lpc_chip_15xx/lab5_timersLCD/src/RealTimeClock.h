/*
 * RealTimeCLock.h
 *
 *  Created on: 13 Oct 2022
 *      Author: Manish
 */

#ifndef REALTIMECLOCK_H_
#define REALTIMECLOCK_H_
#include "Imutex.h"
#include <ctime>

class RealTimeClock {
public:
	RealTimeClock(const tm* time, int ticksPerSecond);
	RealTimeClock(int ticksPerSecond);
	virtual ~RealTimeClock();
	void getTime(tm *now);
	void tick();


private:
	volatile int hour;
	volatile int min;
	volatile int sec;
	Imutex guard;
	int ticksPerSecond;
	int tickCount;
};

#endif /* REALTIMECLOCK_H_ */
