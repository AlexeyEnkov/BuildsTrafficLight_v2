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

	if (resp.equals("OK")) {
		nextState = new ReadIdsState();
	}
	else {
		SystemUtils.printError(resp);

		if (resp.equals("C_ERR"))
		{
			lightStrategy = new BuildServerErrorLightStrategy();
		}
		else
		{
			lightStrategy = new BuildServerRequestErrorLightStrategy(); //todo need to impelment checking in todo that placed upper
		}

		nextState = new ResetModuleState();
	}
}
