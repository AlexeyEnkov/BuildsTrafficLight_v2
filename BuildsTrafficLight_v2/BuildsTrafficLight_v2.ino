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

	//SystemConfig.initFromEEPROM();// init system settings stored in eeprom
//	SystemConfig.updateDebugMode(false); //debug off temporary

	//SoundManager.playInitSound();
	/*
	Serial.println(WifiUtils.reset());
	Serial.println(WifiUtils.testWifi(true));*/
	Serial1.setTimeout(500);
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

//// init
//InitSystemLightStrategy initSystemL;  //0
//// problems
//BuildServerErrorLightStrategy buildServerErrorL; //1
//BuildServerRequestErrorLightStrategy buildServerRequestErrorL; //2
//WiFiConnectionErrorLightStrategy wifiErrorL; //3
//// builds
//BuildsFailedLightStrategy buildsFailedL; //4
//BuildsSuccessLightStrategy buildsSucessedL; //5
//BuildsFailedAndRunningLightStrategy buildsRunningL; //6

/*
	commands map
	L - light (L<NUMBER OF LIGHT STRATEGY>)
	L0,L1,L2,L3,L4,L5,L6
	S - sound (S<NUMBER OF SOUND>)
	S0,S1,S2
	C - config

	Command starts with $ and ends with $.First char is type of command ($<CMD><DATA>$)
*/

void loop() {
	//if (SystemConfig.isDebugMode())
	//{
	//	SystemUtils.printFreeMemory();
	//}

	//// process current state of system (main process)
	//system.process();

	//long del = system.getDelayAfterProcess();
	//boolean needReadConf = true;
	//while (del > 0)
	//{
	//	if (needReadConf)
	//	{
	//		WifiUtils.runScript(F("get_conf.lua"));
	//		String resp = WifiUtils.readResponce();
	//		if (resp.length() > 0 && resp.startsWith(F("CFG:")))
	//		{
	//			resp = resp.substring(4);
	//			//Serial.println(resp);
	//			SystemConfigHelper.handleCfg(resp);
	//		}
	//		needReadConf = false;
	//	}
	//	del -= 10;
	//	delay(10);
	//}
	String input;
	
	if (Serial1.available())
	{
		input = Serial1.readString();
		input.trim();
	}

	if (validateInput(input))
	{
		input = input.substring(1, (input.length() - 1));
		String data = input.substring(1);
		Serial.println(data);
		switch (input.charAt(0))
	{
		case 'L':
			Serial.println("LIGHT");
			break;
		case 'S':
			Serial.println("SOUND");
			break;
		case 'C':
			Serial.println("CONFIG");
			break;
		default:
			break;
		}
	}


	
	}


boolean validateInput(String input)
{
	if (input.length() < 4)
			{
		return false;
			}
	if (!input.startsWith("$"))
	{
		return false;
	}
	if (input.indexOf("$", 1) != (input.length() - 1))
	{
		return false;
	}

	return true;
}

void setLightStrategy(String data)
{

}

void updateSettings(String data)
{

}

void playSound(String data)
{

}