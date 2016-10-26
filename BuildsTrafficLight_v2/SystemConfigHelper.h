// SystemConfigHelper.h

#ifndef _SYSTEMCONFIGHELPER_h
#define _SYSTEMCONFIGHELPER_h

#include "BuildsTrafficLight_v2.h"

#include "SystemConfig.h"
// we need to trigger imediate change of volume
#include "SoundManager.h"

class SystemConfigHelperClass
{
public:

        SystemConfigHelperClass() {}

	void handleCfg(String& rawCfg);

private:
        void handleBrightness(String params);
        void handleSound(String params);
        void handleSoundVolume(String params);
};

static SystemConfigHelperClass SystemConfigHelper;

#endif

