// InitSystemLightStrategy.h

#ifndef _INITSYSTEMLIGHTSTRATEGY_h
#define _INITSYSTEMLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class InitSystemLightStrategy : public BasicLightStrategy {
public:
	void lighting();
private:
	byte curLeds = 4; // 00000100
};

#endif

