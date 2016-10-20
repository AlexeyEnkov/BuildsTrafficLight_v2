// WiFiConnectionErrorLightStrategy.h

#ifndef _WIFICONNECTIONERRORLIGHTSTRATEGY_h
#define _WIFICONNECTIONERRORLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class WiFiConnectionErrorLightStrategy :public BasicLightStrategy {
public:
	void lighting();
private:
	boolean isRedNotYellow = true;
};
#endif

