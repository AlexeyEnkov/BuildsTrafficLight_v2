// 
// 
// 
#include "ReadIdsState.h"
#include "ResetModuleState.h"

ResetModuleState::ResetModuleState() {
	nextState = new ReadIdsState();
}
ResetModuleState::~ResetModuleState() {}

void ResetModuleState::process() {
	Serial.println(F("---ResetModuleState---"));

	boolean forseHardReset = WifiUtils.getModuleHeap() < 22000L;
	if (!WifiUtils.reset(forseHardReset))
	{
		SystemUtils.printError(F("RESET"));
	}
}
