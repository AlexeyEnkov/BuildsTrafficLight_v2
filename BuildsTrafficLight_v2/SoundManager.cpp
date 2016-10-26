// 
// 
// 

#include "SoundManager.h"
#include "DFPlayer_Mini_Mp3.h"

SoundManagerClass SoundManager;

void SoundManagerClass::play(int num)
{
	if (SystemConfig.getSoundParams().isOn == true)
	{
		//setVolume(SystemConfig.getSoundParams().volume);
		mp3_play(num);
	}
}

void SoundManagerClass::stop()
{
	mp3_stop();
}

void SoundManagerClass::sleep()
{
	mp3_sleep();
}

void SoundManagerClass::reset()
{
	mp3_reset();
}

void SoundManagerClass::setVolume(byte volume)
{
	mp3_set_volume(volume);
}

void SoundManagerClass::init(SoftwareSerial &theSerial)
{
	mp3_set_serial(theSerial);
	reset();
	delay(1200);
	setVolume(SystemConfig.getSoundParams().volume);
}