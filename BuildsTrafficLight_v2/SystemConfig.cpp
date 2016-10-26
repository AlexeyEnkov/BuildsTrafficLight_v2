// 
// 
// 

#include "SystemConfig.h"

#define TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR 0 // lenght 1+1+1 = 3 bytes
#define SOUND_PARAMS_EEPROM_ADDR 3 // lenght 1 byte
#define DEBUG_MODE_EEPROM_ADDR 3 // lenght 1 byte

SystemConfigClass SystemConfig;

#ifdef BTL_DEBUG_NO_EEPROM

struct FakeEEPROM {
	void write(int idx, const byte &t) {}
	template< typename T > void put(int idx, const T &t) {}
	template< typename T > void update(int idx, const T &t) {}
};

FakeEEPROM EEPROM;

#else
#include <EEPROM.h>
#endif

void SystemConfigClass::initFromEEPROM()
{
#ifdef BTL_DEBUG_NO_EEPROM
	soundParams.isOn = 1;
	soundParams.volume = 15;
#else
	EEPROM.get(TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR, trLightBrightness);

	SoundParams soundParams;
	byte sndCompact = EEPROM.read(SOUND_PARAMS_EEPROM_ADDR);
	soundParams.isOn = sndCompact >> 5;
	// yes, we don`t need 31(x1f), only from 0 to 30, but it`s ok
	soundParams.volume = sndCompact & 0x1f;

	this->isDebug = (EEPROM.read(DEBUG_MODE_EEPROM_ADDR) != 0 ? true : false);
#endif
}

TrafficLightBrightness SystemConfigClass::getTrafficLightBrightness()
{
	return trLightBrightness;
}

void SystemConfigClass::updateTrafficLightBrightness(TrafficLightBrightness newParams)
{
	this->trLightBrightness = newParams;
	//EEPROM.put(TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR, newParams);
}

const SoundParams& SystemConfigClass::getSoundParams()
{
	return soundParams;
}

void SystemConfigClass::updateSoundParams(const SoundParams& newParams)
{
	this->soundParams = newParams;
	//byte sndCompact = (soundParams.isOn << 5) + soundParams.volume;
	//EEPROM.write(SOUND_PARAMS_EEPROM_ADDR, sndCompact);
}

boolean SystemConfigClass::isDebugMode()
{
	return isDebug;
}

void SystemConfigClass::updateDebugMode(boolean isDebug)
{
	this->isDebug = isDebug;
	//EEPROM.update(DEBUG_MODE_EEPROM_ADDR, (isDebug ? 1 : 0));
}
