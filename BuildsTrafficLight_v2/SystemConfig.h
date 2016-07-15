// SystemConfig.h

#ifndef _SYSTEMCONFIG_h
#define _SYSTEMCONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <EEPROM.h>

#define TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR 0 // lenght 1+1+1 = 3 bytes
#define SOUND_PARAMS_EEPROM_ADDR 3 // lenght 1 byte
#define DEBUG_MODE_EEPROM_ADDR 3 // lenght 1 byte


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
};

class SystemConfigClass
{
 public:
	void initFromEEPROM();

	TrafficLightBrightness getTrafficLightBrightness();
	void updateTrafficLightBrightness(TrafficLightBrightness newParams);

	SoundParams getSoundParams();
	void updateSoundParams(SoundParams newParams);

	boolean isDebugMode();
	void updateDebugMode(boolean isDebug);

private:
	TrafficLightBrightness trLightBrightness;
	SoundParams soundParams;
	boolean isDebug;
};

extern SystemConfigClass SystemConfig;

#endif

