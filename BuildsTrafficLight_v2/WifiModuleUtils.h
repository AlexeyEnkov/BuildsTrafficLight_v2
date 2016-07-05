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
#define ESP_CONNECT_WIFI_TIMEOUT  15000L

class WifiModuleUtils
{
public:

	WifiModuleUtils(void) {};
	~WifiModuleUtils() {};

	void printAvailableAPs();

	boolean reset();
	
	boolean connectWifi();
	void loadSettings();

	void sendCommand(const String command);
	void runScript(String scriptName);

	String readResponce(int timeOut = ESP_RECEIVE_RESPONCE_TIMEOUT);
	void clearInputBuffer(int timeout = 100);
private:
	Stream* moduleStream = &Serial1;
};

static WifiModuleUtils WifiUtils;
#endif

