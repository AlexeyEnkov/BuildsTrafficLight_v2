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

LightTrafficSystem system = LightTrafficSystem(new ReadIdsState(), new InitSystemLightStrategy());

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
	SystemConfig.updateDebugMode(false); //debug off temporary

	SoundManager.playInitSound();
	
	Serial.println(WifiUtils.reset());
	Serial.println(WifiUtils.testWifi(true));
}

boolean isSetupMode = false;

long counter = 0;
long counterTicksForLight = 0;

void routineProcess()
{
	if (counter > FAST_TIMER_TICKS_IN_1SEC / MAIN_TIMER_TICKS_IN_1SEC)
	{
		system.lighting();
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
	system.process();

	long del = system.getDelayAfterProcess();
	boolean needReadConf = true;
	while (del-- > 0)
	{
		if (needReadConf)
		{
			WifiUtils.runScript("get_conf.lua");
			String resp = WifiUtils.readResponce();
			if (resp.length() > 0 && resp.startsWith("CFG:"))
			{
				resp = resp.substring(4);
				//Serial.println(resp);
				SystemConfigHelper.handleCfg(resp);
			}
			needReadConf = false;
		}
		delay(1);
	}
}