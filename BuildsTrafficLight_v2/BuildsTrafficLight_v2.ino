#include "SystemConfigHelper.h"
#include "SoundManager.h"
#include <EEPROM.h>
#include "RtttlPlayer.h"
#include "TestLightStrategy.h"
#include "SystemConfig.h"
#include "WifiModuleUtils.h"
#include "InitSystemLightStrategy.h"
#include "ReadIdsState.h"
#include "SystemUtils.h"
#include "LightTrafficSystem.h"

#include "ResetModuleState.h"

#include <TimerOne.h>

void setup() {

	pinMode(MODULE_RESET_PIN, OUTPUT);
	digitalWrite(MODULE_RESET_PIN, LOW);
	digitalWrite(MODULE_RESET_PIN, HIGH);

	long serialSpeed = 115200;
	Serial.begin(serialSpeed);
	//while (!Serial) {}
	Serial1.begin(serialSpeed);
	while (!Serial1) {}
	
	// uncomment for debug module loop
	/*for (;;) {
	if (Serial.available())  Serial1.write(Serial.read());
	if (Serial1.available()) Serial.write(Serial1.read());
	}*/

	long oneSec = 1000000L;
	Timer1.initialize(oneSec / FAST_TIMER_TICKS_IN_1SEC); // 1 sec/COEFF
	Timer1.stop();
	Timer1.pwm(RED_PIN, 0);
	Timer1.pwm(YELLOW_PIN, 0);
	Timer1.pwm(GREEN_PIN, 0);
	Timer1.attachInterrupt(routineProcess);
	Timer1.start();

	SystemConfig.initFromEEPROM();// init system settings stored in eeprom
	SystemConfig.updateDebugMode(true); //debug off temporary

	SoundManager.playInitSound();
	
	Serial.println(WifiUtils.reset(false));
	Serial.println(WifiUtils.testWifi(true));
}

LightTrafficSystem ltrSystem = LightTrafficSystem(new ReadIdsState(), new InitSystemLightStrategy());

boolean isSetupMode = false;

long counter = 0;
long counterLimit = FAST_TIMER_TICKS_IN_1SEC / MAIN_TIMER_TICKS_IN_1SEC;

void routineProcess()
{
	if (counter > counterLimit)
	{
		ltrSystem.lighting();
		SoundManager.performPlayAction();
		counter = 0;
	}
	counter++;
}

void loop() {
	if (SystemConfig.isDebugMode())
	{
		SystemUtils.printFreeMemory();
	}

	// process current state of system (main process)
	ltrSystem.process();

	// importat to make delay after process 
	long del = ltrSystem.getDelayAfterProcess();
	delay(del);

	WifiUtils.runScript(F("get_conf.lua"));

	Serial.println("bef resp");
	String resp = WifiUtils.readResponce();
	Serial.println(resp.length());
	if (resp.length() > 0 && resp.startsWith(F("CFG:")))
	{
		resp = resp.substring(4);
		SystemConfigHelper.handleCfg(resp);
	}
	Serial.print(F("module heap ")); Serial.println(WifiUtils.getModuleHeap());

}

/*
//TODO pseudo code for feature
get cfg from module

get status OK, C_ERR, R_ERR, OTHER
if OK - get SUCC,RUN,FAIL

C_ERR - WIFI? WifiError or BuildServerError
R_ERR - BuildServerErrorLightStrategy


SUCC - BuildSeccuessLightStr - good sound if need
FAIL - BuildFailedLightStr - fails sound
RUN - BuildFailedAndRunningStr

*/