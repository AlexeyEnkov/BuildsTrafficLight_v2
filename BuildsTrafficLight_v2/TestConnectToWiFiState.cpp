// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "TestConnectToWiFiState.h"
#include "WiFiConnectionErrorLightStrategy.h"

TestConnectToWiFiState::TestConnectToWiFiState() {}

TestConnectToWiFiState::~TestConnectToWiFiState()
{}

void TestConnectToWiFiState::process() {
	Serial.println(F("---TestConnectToWiFiState---"));

	if (WifiUtils.testWifi(false)) {
		nextState = new BuildServerCheckingState();
	}
	else
	{
		SystemUtils.printError(F("WIFI"));
		lightStrategy = new WiFiConnectionErrorLightStrategy();
		delayMs = 10000;
		nextState = new ResetModuleState();
	}
}

