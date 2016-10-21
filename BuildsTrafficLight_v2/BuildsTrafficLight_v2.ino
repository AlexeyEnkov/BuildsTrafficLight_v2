#include "SoundManager.h"
#include "CustomLightStrategy.h"
#include "SystemConfig.h"
#include "WifiModuleUtils.h"
#include "InitSystemLightStrategy.h"
#include "BuildServerErrorLightStrategy.h"
#include "BuildServerRequestErrorLightStrategy.h"
#include "WiFiConnectionErrorLightStrategy.h"
#include "BuildsFailedLightStrategy.h"
#include "BuildsSuccessLightStrategy.h"
#include "BuildsFailedAndRunningLightStrategy.h"
#include "SystemUtils.h"
#include "SystemConfigHelper.h"

SoftwareSerial soundSerial(SERIAL_SOUND_RX, SERIAL_SOUND_TX);
#define Serial1 SERIAL_WIFI

void setup() {
    pinMode(MODULE_RESET_PIN, OUTPUT);
    digitalWrite(MODULE_RESET_PIN, LOW);
    //digitalWrite(MODULE_RESET_PIN, HIGH);

    long serialSpeed = 115200;
    #ifndef BTL_DEBUG_NO_WIFI
    Serial.begin(serialSpeed);
    #endif
    //while (!Serial) {}
    Serial1.begin(serialSpeed);

    // Software serial can operate on 57600,
    // but we need same as on player
    soundSerial.begin(9600);

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

    SystemConfig.initFromEEPROM();
    // on esp
    digitalWrite(MODULE_RESET_PIN, HIGH);

    SoundManager.init(soundSerial);
}

boolean isSetupMode = false;

long counter = 0;
long counterLimit = FAST_TIMER_TICKS_IN_1SEC / MAIN_TIMER_TICKS_IN_1SEC;

BasicLightStrategy* lightStrategy = nullptr;

void routineProcess()
{
    if (counter > counterLimit)
    {
        if (lightStrategy != nullptr)
        {
            lightStrategy->lighting();
        }
        counter = 0;
    }
    counter++;
}



/*
	commands map
	L - light (L<NUMBER OF LIGHT STRATEGY>)
	L0,L1,L2,L3,L4,L5,L6
	S - sound (S<NUMBER OF SOUND>)
	S0,S1,S2,S3
	C - config

	Command starts with $ and ends with $.First char is type of command ($<CMD><DATA>$)
*/

void loop() {
	String input;

	if (Serial1.available())
	{
		input = WifiUtils.readResponce(500);// Serial1.readString();
		input.trim();
                //Serial.println(input); //DEBUG LOG
	}

	if (validateInput(input))
	{
		SystemUtils.printFreeMemory();
		String data = input.substring(1);
		Serial.print(F("cmd:\t"));
		switch (input.charAt(0))
		{
		case 'L':
			Serial.print(F("LIGHT"));
			setLightStrategy(data);
			break;
		case 'S':
			Serial.print(F("SOUND"));
			playSound(data);
			break;
		case 'C':
			Serial.print(F("CONFIG"));
			updateSettings(data);
			break;
		default:
			break;
		}
                Serial.print(F("\tdata:\t")); Serial.println(data);
	}
}


boolean validateInput(String input)
{
	if (input.length() < 2)
	{
		return false;
	}
	char cmd = input.charAt(0);
	if (cmd != 'L' && cmd != 'C' && cmd != 'S')
	{
		return false;
	}
	return true;
}

/*
## init
0 - InitSystemLightStrategy
## problems
1 - BuildServerErrorLightStrategy
2 - BuildServerRequestErrorLightStrategy
3 - WiFiConnectionErrorLightStrategy
## builds
4 - BuildsFailedLightStrategy
5 - BuildsSuccessLightStrategy
6 - BuildsFailedAndRunningLightStrategy
*/


BasicLightStrategy* lightStrategies[] = {
	0,
	new InitSystemLightStrategy,
	new BuildServerErrorLightStrategy,
	new BuildServerRequestErrorLightStrategy,
	new WiFiConnectionErrorLightStrategy,
	new BuildsFailedLightStrategy,
	new BuildsSuccessLightStrategy,
	new BuildsFailedAndRunningLightStrategy,
	new CustomLightStrategy
};

void setLightStrategy(String data)
{
	int lightNum = data.substring(0, 1).toInt();

	if (lightNum >= 0 && lightNum <= 7)
	{
		BasicLightStrategy* newLightStrategy = lightStrategies[lightNum + 1]; // shift by one because 0 is null_ptr
		if (newLightStrategy != lightStrategy)
		{
			lightStrategy = newLightStrategy;
			lightStrategy->reset();
		}
		if (lightNum == 7)
		{
			String leds = data.substring(1);
			lightStrategy->setLeds(leds.charAt(0)=='1', leds.charAt(1)=='1', leds.charAt(2)=='1');
		}
		
	}
}

void updateSettings(String data)
{
	SystemConfigHelper.handleCfg(data);
}

/*
- - Stop playing
0 - Init system sound
1 - Sound for good build
2 - Sound for failed build
3 - Sound for on sound
*/

void playSound(String data)
{
    if(data.charAt(0) == '-')
        SoundManager.stop();
    else
        SoundManager.play(data.toInt()+1);
}
