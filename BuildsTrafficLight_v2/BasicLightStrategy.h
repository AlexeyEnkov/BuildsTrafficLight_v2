// BasicLightStrategy.h

#ifndef _BASICLIGHTSTRATEGY_h
#define _BASICLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include <TimerOne.h>
#include "SystemUtils.h"
#include "SystemConfig.h"

class BasicLightStrategy {
public:
	virtual ~BasicLightStrategy() {};
	virtual void lighting() = 0; // one in 1/1000 sec
	void setLeds(boolean red, boolean yellow, boolean green);
	void light();
	void reset() { innerCounter = 0; };
protected:
	int getDutyFromPercents(byte percents);
	long innerCounter;
	long countsFor1Sec = 1 * MAIN_TIMER_TICKS_IN_1SEC; // 1 sec
	boolean red;
	boolean yellow;
	boolean green;
};

#endif

