// 
// 
// 

#include "SystemUtils.h"

int SystemUtils_::freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void SystemUtils_::printError(String error)
{
	Serial.print(F("error: ")); Serial.println(error);
}

void SystemUtils_::printFreeMemory()
{
	Serial.print(F("free ram: ")); Serial.println(freeRam());
}

boolean SystemUtils_::isTimeForUpdateIds()
{
	if (timeForUpdateIds < millis())
	{
		Serial.print(F("in get time for update ")); printFreeMemory();
		timeForUpdateIds = millis() + MS_BETWEEN_UP_IDS;
		return true;
	}
	return false;
}
