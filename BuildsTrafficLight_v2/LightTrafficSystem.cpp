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
	lightLock = true;
	if (currentState->getLightStrategy() != 0) {
		delete currentLightStrategy;
		currentLightStrategy = currentState->getLightStrategy();
	}
	lightLock = false;
}

long LightTrafficSystem::getDelayAfterProcess()
{
	return delayAfterProcess;
}

void LightTrafficSystem::process() {
	currentState->process();

	updateLightStrategy();
	
	delayAfterProcess = currentState->getDelayAfterProcessState();

	setCurrentState();
}

void LightTrafficSystem::lighting() {
	if (!lightLock) {
		currentLightStrategy->lighting();
	}
}
