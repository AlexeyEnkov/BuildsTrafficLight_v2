// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "TestConnectToWiFiState.h"
#include "WiFiConnectionErrorLightStrategy.h"

TestConnectToWiFiState::TestConnectToWiFiState() {}

TestConnectToWiFiState::~TestConnectToWiFiState() {}

void TestConnectToWiFiState::process() {
	Serial.println(F("---TestConnectToWiFiState---"));

	if (WifiUtils.testWifi(true)) {
		nextState = new BuildServerCheckingState();
	}
	else
	{
		SystemUtils.printError(F("WIFI"));
		lightStrategy = new WiFiConnectionErrorLightStrategy();
		delayMs = 1000;
		nextState = new ResetModuleState();
	}
}

