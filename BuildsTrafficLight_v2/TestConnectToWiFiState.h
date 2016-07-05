// TestConnectToWiFiState.h

#ifndef _CONNECTTOWIFISTATE_h
#define _CONNECTTOWIFISTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"

class TestConnectToWiFiState : public SystemState {
public:
	TestConnectToWiFiState();
	~TestConnectToWiFiState();

	void process();

};

#endif