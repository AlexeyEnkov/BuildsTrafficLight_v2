// 
// 
// 

#include "SystemConfigHelper.h"

// we need to trigger imediate change of volume
#include "SoundManager.h"

void SystemConfigHelperClass::handleCfg(String & rawCfg)
{
	String curParam = "";
	int startParamInd = 0;
	int delimInd = rawCfg.indexOf(";", startParamInd);
	while (delimInd != -1)
	{
		curParam = rawCfg.substring(startParamInd, delimInd);
		startParamInd = delimInd + 1;
		if (curParam.startsWith(F("br=")))
		{
			handleBrightness(curParam.substring(3));
		}
                else if (curParam.startsWith(F("sound=")))
		{
			handleSound(curParam.substring(6));
		}
                else if (curParam.startsWith(F("vol=")))
                {
                        handleSoundVolume(curParam.substring(4));
                }
		delimInd = rawCfg.indexOf(";", startParamInd);
	}
}

void SystemConfigHelperClass::handleBrightness(String && params)
{
	TrafficLightBrightness newParam;
	int startInd = 0;
	int delimeterInd = 0;
	while (delimeterInd != -1)
	{
		delimeterInd = params.indexOf(",", startInd);
		String val;
		if (delimeterInd == -1)
		{
			val = params.substring(startInd + 2);
		}
		else
		{
			val = params.substring(startInd + 2, delimeterInd);
		}
		char typeOfLed = params.charAt(startInd);
		byte percVal = val.toInt();
		percVal = percVal > 100 || percVal < 0 ? 0 : percVal;
		switch (typeOfLed)
		{
		case 'r':
			newParam.red = percVal;
			break;
		case 'y':
			newParam.yellow = percVal;
			break;
		case 'g':
			newParam.green = percVal;
			break;
		}
		startInd = delimeterInd + 1;
	}
	TrafficLightBrightness oldParam = SystemConfig.getTrafficLightBrightness();
	if (oldParam.green != newParam.green ||
		oldParam.red != newParam.red ||
		oldParam.yellow != newParam.yellow)
	{
		SystemConfig.updateTrafficLightBrightness(newParam);
	}

}

void SystemConfigHelperClass::handleSound(String && params)
{
    byte isOn = params.equalsIgnoreCase("1") ? 1 : 0;

    if (isOn != SystemConfig.getSoundParams().isOn)
    {
        SoundParams newParams = SystemConfig.getSoundParams();
        newParams.isOn = isOn;
        SystemConfig.updateSoundParams(newParams);
    }

}

void SystemConfigHelperClass::handleSoundVolume(String && params)
{
    uint8_t volume = params.toInt();
    if (volume != SystemConfig.getSoundParams().volume
            // Sound volume from 0 to 30
            && volume<31)
    {
        SoundManager.setVolume(volume);
        SoundParams newParams = SystemConfig.getSoundParams();
        newParams.volume = volume;
        SystemConfig.updateSoundParams(newParams);
    }
}
