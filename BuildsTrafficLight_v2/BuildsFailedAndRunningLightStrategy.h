// BuildsFailedAndRunning.h

#ifndef _BUILDSFAILEDANDRUNNING_h
#define _BUILDSFAILEDANDRUNNING_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class BuildsFailedAndRunningLightStrategy:public BasicLightStrategy {
public: 
	BuildsFailedAndRunningLightStrategy();
	void lighting();
};
#endif

