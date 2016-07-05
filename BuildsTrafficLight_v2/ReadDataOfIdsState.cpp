// 
// 
// 

#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "BuildsFailedAndRunningLightStrategy.h"
#include "BuildsFailedLightStrategy.h"
#include "BuildsSuccessLightStrategy.h"
#include "TestConnectToWifiState.h"


ReadDataOfIdsState::ReadDataOfIdsState() {
	MAX_REPEATS = 2;
}

ReadDataOfIdsState::~ReadDataOfIdsState() {

}

void ReadDataOfIdsState::process() {
	Serial.println(F("---ReadDataOfIdsState---"));

	STATE_OF_BUILDS = SUCCESS;

	WifiUtils.clearInputBuffer();
	Serial1.println("dofile(\"get_stat.lua\")");
	String resp;
	boolean isGetOKResp = WifiUtils.readResponce(resp, 10000) && resp.equalsIgnoreCase("OK"); 
	
	// choose next state
	if (isGetOKResp) {
		resp = "";
		WifiUtils.readResponce(resp);
		Serial.println(resp);

		delayMs = 5000; // msec if all good
		nextState = new ReadIdsState();

		// change light strategy
		if (resp.equalsIgnoreCase(F("FAIL")))
		{
			lightStrategy = new BuildsFailedLightStrategy();
			SoundManager.playBadSound();
		}
		else if (resp.equalsIgnoreCase(F("RUN")))
		{
			lightStrategy = new BuildsFailedAndRunningLightStrategy();
			SoundManager.clearPrevPlayedSoundType();
		}
		else
		{
			lightStrategy = new BuildsSuccessLightStrategy();
			SoundManager.playGoodSound();
		}
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