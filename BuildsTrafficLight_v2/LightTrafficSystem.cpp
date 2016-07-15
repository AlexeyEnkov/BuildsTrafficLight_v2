// 
// 
// 

#include "LightTrafficSystem.h"
#include "ReadIdsState.h"


LightTrafficSystem::LightTrafficSystem(SystemState* st, BasicLightStrategy* lstr) {
	currentState = st;
	currentLightStrategy = lstr;
};

void LightTrafficSystem::setCurrentState() {
	if (currentState->getNextState() != 0) {
		SystemState* newState = currentState->getNextState();
		delete currentState;
		currentState = newState;
	}
}

void LightTrafficSystem::updateLightStrategy() {
	// update light strategy
	if (currentState->getLightStrategy() != 0) {
		delete currentLightStrategy;
		currentLightStrategy = 0;

		currentLightStrategy = currentState->getLightStrategy();
	}
}

long LightTrafficSystem::getDelayAfterProcess()
{
	return delayAfterProc;
}

void LightTrafficSystem::process() {
	currentState->process();

	delayAfterProc = currentState->getDelayAfterProcessState();

	updateLightStrategy();

	setCurrentState();
}

void LightTrafficSystem::lighting() {
	if (currentLightStrategy != 0) {
		currentLightStrategy->lighting();
	}
}
