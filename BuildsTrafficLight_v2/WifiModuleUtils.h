// WifiModuleUtils.h

#ifndef _WIFIMODULEUTILS_h
#define _WIFIMODULEUTILS_h

#include "BuildsTrafficLight_v2.h"

#include "SystemUtils.h"
#include "SystemConfig.h"

#define ESP_RECEIVE_RESPONCE_TIMEOUT   1500L
#define ESP_RESET_TIMEOUT     2000L
#define ESP_CONNECT_WIFI_TIMEOUT  15000L

class WifiModuleUtils
{
public:

	WifiModuleUtils(void) {};
	~WifiModuleUtils() {};

	boolean reset(boolean forseHardReset);
	
	boolean testWifi(boolean reconnect);

	long getModuleHeap();
	void sendCommand(const String command);
	void runScript(String scriptName);

	String readResponce(int timeOut = ESP_RECEIVE_RESPONCE_TIMEOUT);
	void clearInputBuffer(int timeout = 100);
private:
	Stream* moduleStream = &SERIAL_WIFI;
};

static WifiModuleUtils WifiUtils;
#endif

