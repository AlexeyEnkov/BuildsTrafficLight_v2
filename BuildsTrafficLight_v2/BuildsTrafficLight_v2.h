#ifndef BuildsTrafficLight_v2_h
#define BuildsTrafficLight_v2_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BTL_DEBUG_NO_WIFI
#define BTL_DEBUG_NO_EEPROM

#ifdef BTL_DEBUG_NO_WIFI
#define SERIAL_WIFI Serial
#else
#define SERIAL_WIFI Serial1
#endif

#define SERIAL_DEBUG Serial

#endif
