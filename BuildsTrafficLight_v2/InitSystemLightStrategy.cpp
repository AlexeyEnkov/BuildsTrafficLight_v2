// 
// 
// 

#include "InitSystemLightStrategy.h"

void InitSystemLightStrategy::lighting() {
	if (innerCounter < (countsFor1Sec/3)) {
		innerCounter++;
	}
	else {
		innerCounter = 0;
		curLeds >>= 1;
		if (curLeds == 0) {
			curLeds = 4;
		}
	}
	setLeds(curLeds & 0x4, curLeds & 0x2 , curLeds & 0x1);
	light();
}
