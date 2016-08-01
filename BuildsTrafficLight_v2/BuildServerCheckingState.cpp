// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "BuildServerErrorLightStrategy.h"
#include "BuildServerRequestErrorLightStrategy.h"
#include "ReadIdsState.h"

BuildServerCheckingState::BuildServerCheckingState() {
}

BuildServerCheckingState::~BuildServerCheckingState() 
{}

void BuildServerCheckingState::process() {
	Serial.println(F("---BuildServerCheckingState---"));

	WifiUtils.runScript(F("test_build_srv.lua"));
	String resp = WifiUtils.readResponce(15000);

	if (!resp.equals(RESP_OK)) {
		SystemUtils.printError(resp);

		if (resp.equals(RESP_CONN_ERR))
		{
			lightStrategy = new BuildServerErrorLightStrategy();
		}
		else
		{
			lightStrategy = new BuildServerRequestErrorLightStrategy();
		}
	}
	nextState = new ResetModuleState();
}
