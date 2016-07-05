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
	WifiUtils.clearInputBuffer(1000); // read resp from module
}

void WifiModuleUtils::sendCommand(const String & command)
{
	clearInputBuffer();
	moduleStream->print(command);
}

void WifiModuleUtils::runScript(String & scriptName)
{
	clearInputBuffer();
	moduleStream->print(F("dofile(\"")); moduleStream->print(scriptName); moduleStream->println("\")");
}

boolean WifiModuleUtils::readResponce(String & resp, int timeOut)
{
	moduleStream->setTimeout(timeOut);
	boolean res = moduleStream->find("$");
	if (res)
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
		res = true;
	}
	return res;
}

byte WifiModuleUtils::convertModuleRespToRespCode(String & resp)
{
	return byte();
}

void WifiModuleUtils::clearInputBuffer(int timeout)
{
	moduleStream->setTimeout(timeout);
	String trash = moduleStream->readString();
}