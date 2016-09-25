// 
// 
// 

#include "BuildServerRequestErrorLightStrategy.h"


void BuildServerRequestErrorLightStrategy::lighting() {
	if (innerCounter < countsFor1Sec) {
		innerCounter++;
	}
	else {
		yellowLed = !yellowLed;
		innerCounter = 0;
	}
	setLeds(false, yellowLed, false);
	light();
}