// SoundManager.h

#ifndef _SOUNDMANAGER_h
#define _SOUNDMANAGER_h

#include "BuildsTrafficLight_v2.h"

#include "SystemConfig.h"
#include "SoftwareSerial.h"

class SoundManagerClass
{

public:
	// play sound from 1 to 2999
	void play(int num);

	void stop();

	void sleep();
	void reset();

	void setVolume(byte volume);

	// init called after loading settings
	void init(SoftwareSerial &theSerial);
};

extern SoundManagerClass SoundManager;

#endif

