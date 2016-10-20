// 
// 
// 

#include "SoundManager.h"
#include "SystemConfig.h"

#include <DFPlayer_Mini_Mp3.h>

SoundManagerClass SoundManager;

void SoundManagerClass::play(uint8_t num)
{
    if (SystemConfig.getSoundParams().isOn == true)
    {
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

void SoundManagerClass::setVolume(uint8_t volume)
{
    mp3_set_volume(volume);
}

void SoundManagerClass::init()
{
    setVolume(SystemConfig.getSoundParams().volume);
}

void SoundManagerClass::init(SoftwareSerial &theSerial)
{
    mp3_set_serial(theSerial);
    init();
}

void SoundManagerClass::init(HardwareSerial &theSerial)
{
    mp3_set_serial(theSerial);
    init();
}

void SoundManagerClass::setDebugSerial(HardwareSerial &theSerial)
{
    mp3_set_debug_serial(theSerial);
}
