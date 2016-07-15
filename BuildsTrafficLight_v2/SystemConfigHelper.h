// SystemConfigHelper.h

#ifndef _SYSTEMCONFIGHELPER_h
#define _SYSTEMCONFIGHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemConfig.h"

class SystemConfigHelperClass
{
public:

	SystemConfigHelperClass() {};

	void handleCfg(String& rawCfg);

private:
	void handleBrightness(String params);
	void handleSound(String params);
};

static SystemConfigHelperClass SystemConfigHelper;

#endif

