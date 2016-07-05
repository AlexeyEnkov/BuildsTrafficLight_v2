// WifiModuleUtils.h

#ifndef _WIFIMODULEUTILS_h
#define _WIFIMODULEUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemUtils.h"
#include "SystemConfig.h"

#define ESP_RECEIVE_RESPONCE_TIMEOUT   1500L
#define ESP_RESET_TIMEOUT     5000L
#define ESP_CONNECT_AP_TIMEOUT  10000L

class WifiModuleUtils
{
public:

	WifiModuleUtils(void) {};
	~WifiModuleUtils() {};

	void printAvailableAPs();

	boolean reset();

	void sendCommand(const String& command);
	void runScript(String& scriptName);

	boolean readResponce(String& resp, int timeOut = ESP_RECEIVE_RESPONCE_TIMEOUT);
	byte convertModuleRespToRespCode(String& resp);
	void clearInputBuffer(int timeout = 100);
private:
	Stream* moduleStream = &Serial1;
};

static WifiModuleUtils WifiUtils;
#endif

