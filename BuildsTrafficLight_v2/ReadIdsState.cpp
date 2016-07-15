// 
// 
// 

#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "TestConnectToWifiState.h"

ReadIdsState::ReadIdsState() {}

ReadIdsState::~ReadIdsState()
{}

// read ids to eeprom 
void ReadIdsState::process() {
	nextState = new ReadDataOfIdsState();

	if (!SystemUtils.isTimeForUpdateIds())
	{
		return;
	}
	Serial.println(F("---ReadIdsState---"));

	WifiUtils.runScript("upd_ids.lua");
	String resp = WifiUtils.readResponce(15000);

	if (!resp.equalsIgnoreCase("OK")) {
		SystemUtils.printError(resp);
		nextState = new TestConnectToWiFiState();
		delayMs = 5000;
	}
}

