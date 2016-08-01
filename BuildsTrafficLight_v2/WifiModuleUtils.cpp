// 
// 
// 

#include "WifiModuleUtils.h"

boolean WifiModuleUtils::reset(boolean forseHardReset)
{
	clearInputBuffer();
	if (!forseHardReset)
	{
		sendCommand(F("require(\"send_resp\")(\"OK\")"));
		if (String(RESP_OK).equals(readResponce(1000)))
		{
			return true;
		}
		clearInputBuffer();
	}
	// hard reset of wifi module
	digitalWrite(MODULE_RESET_PIN, LOW);
	delay(200);
	digitalWrite(MODULE_RESET_PIN, HIGH);
	delay(1000);
	sendCommand(F("node.restart()"));
	return String(RESP_OK).equals(readResponce(ESP_RESET_TIMEOUT));
}

boolean WifiModuleUtils::testWifi(boolean reconnect)
{
	clearInputBuffer();
	String script = F("require(\"test_wifi\")(");
	script += (reconnect ? F("true") : F("false"));
	script += ")";
	sendCommand(script);
	return String(F("OK")).equals(readResponce(ESP_CONNECT_WIFI_TIMEOUT));
}

long WifiModuleUtils::getModuleHeap()
{
	sendCommand(F("require(\"send_resp\")(node.heap())"));
	String heap = readResponce();
	if (heap.length() == 0)
	{
		return 0;
	}
	char buf[12];
	heap.toCharArray(buf, 12);
	return atol(buf);
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
	String resp = "RESP_ERR";
	//moduleStream->setTimeout(timeOut);
	moduleStream->setTimeout(1500);
	Serial.println(moduleStream->readString());
	return "OK";
	if (moduleStream->find("$"))
	{
		resp = "";
		char c;
		int respTimeout = 300;
		while (respTimeout > 0)
		{
			boolean cancel = false;
			while (moduleStream->available())
			{
				c = moduleStream->read();
				if (c == '\n' || c == '\r')
				{
					cancel = true;
					break;
				}
				else
				{
					resp += c;
				}
			}
			if (cancel)
			{
				break;
			}
			respTimeout -= 10;
			delay(10);
		}
	}
	return resp;
}

void WifiModuleUtils::clearInputBuffer(int timeout)
{
	moduleStream->setTimeout(timeout);
	moduleStream->readString();
}