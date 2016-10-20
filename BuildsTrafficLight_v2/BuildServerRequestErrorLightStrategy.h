// BuildServerRequestErrorLightStrategy.h

#ifndef _BUILDSERVERREQUESTERRORLIGHTSTRATEGY_h
#define _BUILDSERVERREQUESTERRORLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class BuildServerRequestErrorLightStrategy :public BasicLightStrategy {
public:
	void lighting();
private:
	boolean yellowLed = true;
};

#endif

