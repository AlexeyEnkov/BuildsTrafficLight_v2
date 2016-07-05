// 
// 
// 

#include "WifiModuleUtils.h"


void WifiModuleUtils::printAvailableAPs()
{
	Serial.println("not impl");
}

boolean WifiModuleUtils::reset()
{
	// hard reset of wifi module
	digitalWrite(MODULE_RESET_PIN, LOW);
	delay(100);
	digitalWrite(MODULE_RESET_PIN, HIGH);
	delay(1000);
	return String("OK").equals(readResponce(ESP_RESET_TIMEOUT));
}

boolean WifiModuleUtils::connectWifi()
{
	runScript(F("wifi_con.lua"));
	return String("OK").equals(readResponce(ESP_CONNECT_WIFI_TIMEOUT));
}

void WifiModuleUtils::loadSettings()
{
	moduleStream->print(F("require(\"upd_cfg\")(\""));
	moduleStream->print(SystemConfig.getWifiParams().ssid);
	moduleStream->print(F("\",\""));
	moduleStream->print(SystemConfig.getWifiParams().pass);
	moduleStream->print(F("\",\""));
	moduleStream->print(SystemConfig.getBuildServerParams().ip);
	moduleStream->print(F("\",\""));
	moduleStream->print(SystemConfig.getBuildServerParams().port);
	moduleStream->println(F("\")"));
}

void WifiModuleUtils::sendCommand(const String command)
{
	clearInputBuffer();
	moduleStream->println(command);
}

void WifiModuleUtils::runScript(String scriptName)
{
	clearInputBuffer();
	moduleStream->print(F("dofile(\"")); moduleStream->print(scriptName); moduleStream->println(F("\")"));
}

String WifiModuleUtils::readResponce(int timeOut)
{
	String resp;
	moduleStream->setTimeout(timeOut);
	if (moduleStream->find("$"))
	{
		char c;
		int nextTimeout = 200;
		while (nextTimeout-- > 0)
		{
			while (moduleStream->available() && c != '\n')
			{
				c = moduleStream->read();
				resp += c;
			}
			delay(1);
		}
		resp.trim();
	}
	return resp;
}

void WifiModuleUtils::clearInputBuffer(int timeout)
{
	moduleStream->setTimeout(timeout);
	String trash = moduleStream->readString();
}