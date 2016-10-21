// SoundManager.h

#ifndef _SOUNDMANAGER_h
#define _SOUNDMANAGER_h

#include "BuildsTrafficLight_v2.h"

#include <SoftwareSerial.h>

class SoundManagerClass
{
public:
    // play sound from 1 to 255
    void play(uint8_t num);

    void stop();

    void sleep();
    void reset();

    void setVolume(uint8_t volume);

    // init called after loading settings
    void init(SoftwareSerial &theSerial);
    void init(HardwareSerial &theSerial);

    void setDebugSerial(HardwareSerial &theSerial);
private:
    void init();
};

extern SoundManagerClass SoundManager;

#endif

