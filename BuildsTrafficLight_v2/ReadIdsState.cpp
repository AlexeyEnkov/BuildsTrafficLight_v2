// 
// 
// 

#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "TestConnectToWifiState.h"

ReadIdsState::ReadIdsState() {
	MAX_REPEATS = 1;
}

ReadIdsState::~ReadIdsState()
{}

// read ids to eeprom 
void ReadIdsState::process() {

	Serial.println(F("---ReadIdsState---"));

	WifiUtils.clearInputBuffer();
	Serial1.println("dofile(\"upd_ids.lua\")");
	String resp;
	boolean isGetResp = WifiUtils.readResponce(resp, 15000);
	// todo fin resp
	// todo update if need one in 5 minutes ?
	// todo resp status from module
	//byte respStatus = NO_ERRORS;

	if (isGetResp && resp.equalsIgnoreCase("OK")) {
		nextState = new ReadDataOfIdsState();
	}
	else {
		//SystemUtils.printError(respStatus);

		if (countOfRepeats < MAX_REPEATS) {
			countOfRepeats++;
		}
		else {
			nextState = new TestConnectToWiFiState();
		}
	}
}

