// 
// 
// 

#include "WifiModuleUtils.h"

boolean WifiModuleUtils::reset()
{
	// hard reset of wifi module
	digitalWrite(MODULE_RESET_PIN, LOW);
	delay(200);
	digitalWrite(MODULE_RESET_PIN, HIGH);
	delay(1000);
	sendCommand("node.restart()");
//	Serial.println(moduleStream->readString());
//	Serial.println(moduleStream->readString());
	return String("OK").equals(readResponce(ESP_RESET_TIMEOUT));
}

boolean WifiModuleUtils::testWifi(boolean reconnect)
{
	if (reconnect)
	{
		runScript(F("test_wifi.lua"));
	}
	else
	{
		sendCommand("print((wifi.sta.getip() and '$OK' or '$ERR'))");
	}
	
	return String("OK").equals(readResponce(ESP_CONNECT_WIFI_TIMEOUT));
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