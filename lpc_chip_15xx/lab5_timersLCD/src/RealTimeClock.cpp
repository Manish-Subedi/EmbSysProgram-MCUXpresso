/*
 * RealTimeCLock.cpp
 *
 *  Created on: 13 Oct 2022
 *      Author: Manish
 */

#include "RealTimeClock.h"

#include <ctime>
#include <mutex>
#include "Imutex.h"

RealTimeClock::RealTimeClock(int ticksPerSecond):ticksPerSecond(ticksPerSecond) {
	hour = 23;
	min = 58;
	sec = 35;
}
RealTimeClock::RealTimeClock(const tm* time, int ticksPerSecond):ticksPerSecond(ticksPerSecond) {
	hour = time->tm_hour;
	min = time->tm_min;
	sec = time->tm_sec;

}
void RealTimeClock::getTime(tm *now){
	std::lock_guard<Imutex> lock(guard);
	now->tm_hour = hour;
	now->tm_min = min;
	now->tm_sec = sec;
}

void RealTimeClock::tick(){
	tickCount++;
	if(tickCount >= ticksPerSecond){
		tickCount = 0;
		sec++;
		if(sec>59){
			sec=0;
			min++;
			if(min>59){
				min=0;
				hour++;
				if(hour>23){
					hour=0;
				}
			}
		}
	}
}
RealTimeClock::~RealTimeClock() {
	// TODO Auto-generated destructor stub
}

