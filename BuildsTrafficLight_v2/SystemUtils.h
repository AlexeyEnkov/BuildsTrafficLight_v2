// Utils.h

#ifndef _SYSTEMUTILS_h
#define _SYSTEMUTILS_h

#include "BuildsTrafficLight_v2.h"

#include "EEPROM.h"

#define xstr(s) str(s)
#define str(s) #s

//define error codes


#define MS_BETWEEN_UP_IDS 60000L // 

#define RED_PIN 11
#define YELLOW_PIN 10
#define GREEN_PIN 9

#define SERIAL_SOUND_RX 7
#define SERIAL_SOUND_TX 8

#define MAIN_TIMER_TICKS_IN_1SEC 20 // times is 1 sec
#define FAST_TIMER_TICKS_IN_1SEC 500 // determine frequency of pwm (adjusted for traffic light led lamps) need 500

#define MODULE_RESET_PIN 2

class SystemUtils_ {

public:

	SystemUtils_(void) {};
	~SystemUtils_() {};

	int freeRam();

	void printError(String err);
	void printFreeMemory();
	boolean isTimeForUpdateIds();
private:
	unsigned long timeForUpdateIds = 0;
};

extern SystemUtils_ SystemUtils;
#endif


