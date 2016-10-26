// BuildsSuccessLightStrategy.h

#ifndef _BUILDSSUCCESSLIGHTSTRATEGY_h
#define _BUILDSSUCCESSLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class BuildsSuccessLightStrategy : public BasicLightStrategy {

public:
	BuildsSuccessLightStrategy();
	void lighting();
};
#endif

