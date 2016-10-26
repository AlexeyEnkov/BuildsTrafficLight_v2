// BuildServerErrorLightStrategy.h

#ifndef _BUILDSERVERERRORLIGHTSTRATEGY_h
#define _BUILDSERVERERRORLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class BuildServerErrorLightStrategy :public BasicLightStrategy {
public:
	void lighting();
private:
	boolean redLed = true;
};
#endif

