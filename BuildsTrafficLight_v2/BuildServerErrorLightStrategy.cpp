// 
// 
// 

#include "BuildServerErrorLightStrategy.h"

void BuildServerErrorLightStrategy::lighting(){
	if (innerCounter < countsFor1Sec) {
		innerCounter++;
	}
	else {
		redLed = !redLed;
		innerCounter = 0;
	}
	setLeds(redLed, false, false);
	light();
}
