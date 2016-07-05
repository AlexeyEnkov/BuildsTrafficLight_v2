// 
// 
// 

#include "SystemUtils.h"

int SystemUtils_::freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void SystemUtils_::printError(byte error)
{
	Serial.print(F("error: ")); Serial.println(error);
}

void SystemUtils_::printFreeMemory()
{
	Serial.print(F("free ram: ")); Serial.println(freeRam());
}