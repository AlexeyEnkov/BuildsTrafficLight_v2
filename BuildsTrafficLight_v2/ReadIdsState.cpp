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

	Serial.println(F("---ReadIdsState---"));

	WifiUtils.runScript("upd_ids.lua");
	String resp = WifiUtils.readResponce(15000);
	delayMs = 2000;

	if (!resp.equalsIgnoreCase(RESP_OK)) {
		SystemUtils.printError(resp);
		nextState = new TestConnectToWiFiState();
	}
	else
	{
		nextState = new ReadDataOfIdsState();
	}
}

