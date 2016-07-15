// 
// 
// 

#include "SystemConfigHelper.h"

void SystemConfigHelperClass::handleCfg(String & rawCfg)
{
	int startParamInd = 0;
	int delimInd = 0;
	String curParam = "";
	while (startParamInd < rawCfg.length())
	{
		delimInd = rawCfg.indexOf(";", startParamInd);
		curParam = rawCfg.substring(startParamInd, delimInd);
		startParamInd = delimInd + 1;
		if (curParam.startsWith("br"))
		{
			handleBrightness(curParam.substring(3));
		}
		if (curParam.startsWith("sound"))
		{
			handleSound(curParam.substring(6));
		}
	}
}

void SystemConfigHelperClass::handleBrightness(String params)
{
	TrafficLightBrightness newParam;
	int stInd = 0;
	int delInd = 0;
	while (delInd != -1)
	{
		delInd = params.indexOf(",", stInd);
		String val;
		if (delInd == -1)
		{
			val = params.substring(stInd+2);
		}
		else
		{
			val = params.substring(stInd+2, delInd);
		}
		char typeOfLed = params.charAt(stInd);
		byte percVal = val.toInt();
		percVal = percVal > 100 ? 100 : percVal;
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
		stInd = delInd + 1;
	}
	TrafficLightBrightness oldParam = SystemConfig.getTrafficLightBrightness();
	if (oldParam.green != newParam.green ||
		oldParam.red != newParam.red ||
		oldParam.yellow != newParam.yellow)
	{
		SystemConfig.updateTrafficLightBrightness(newParam);
	}
	
}

void SystemConfigHelperClass::handleSound(String params)
{
	SoundParams newParams;
	newParams.isOn = params.equalsIgnoreCase("1") ? 1 : 0;
	if (newParams.isOn != SystemConfig.getSoundParams().isOn)
	{
		SystemConfig.updateSoundParams(newParams);
	}
	
}
