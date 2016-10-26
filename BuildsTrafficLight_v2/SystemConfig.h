// SystemConfig.h

#ifndef _SYSTEMCONFIG_h
#define _SYSTEMCONFIG_h

#include "BuildsTrafficLight_v2.h"

#define RESP_OK F("OK")
#define RESP_CONN_ERR F("C_ERR")
#define RESP_REQ_ERR F("R_ERR")

// in percents 
struct TrafficLightBrightness
{
	byte red;
	byte yellow;
	byte green;
};

struct SoundParams
{
	byte isOn;
	byte volume;
};

class SystemConfigClass
{
public:
	void initFromEEPROM();

	TrafficLightBrightness getTrafficLightBrightness();
	void updateTrafficLightBrightness(TrafficLightBrightness newParams);

	const SoundParams& getSoundParams();
	void updateSoundParams(const SoundParams& newParams);

	boolean isDebugMode();
	void updateDebugMode(boolean isDebug);

private:
	TrafficLightBrightness trLightBrightness;
	SoundParams soundParams;
	boolean isDebug;
};

extern SystemConfigClass SystemConfig;

#endif

