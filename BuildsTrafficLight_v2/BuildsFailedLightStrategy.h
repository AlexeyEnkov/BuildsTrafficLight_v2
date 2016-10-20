// BuildsFailedLightStrategy.h

#ifndef _BUILDSFAILEDLIGHTSTRATEGY_h
#define _BUILDSFAILEDLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class BuildsFailedLightStrategy :public BasicLightStrategy {
public:
	BuildsFailedLightStrategy();
	void lighting();
};
#endif

