// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "TestConnectToWiFiState.h"
#include "WiFiConnectionErrorLightStrategy.h"

TestConnectToWiFiState::TestConnectToWiFiState() {
	MAX_REPEATS = 0;// try to connect if not success -> reset module
}

TestConnectToWiFiState::~TestConnectToWiFiState()
{}

void TestConnectToWiFiState::process() {
	Serial.println(F("---TestConnectToWiFiState---"));

	WifiUtils.reset();
	delay(1000);
	if (true /*== WifiUtils.connectToAP()*/) {
		nextState = new BuildServerCheckingState();
	}
	else
	{
		SystemUtils.printError(WIFI_CONNECTION_ERROR);
		lightStrategy = new WiFiConnectionErrorLightStrategy();
		delayMs = 1000;
		nextState = new ResetModuleState();
	}
}

