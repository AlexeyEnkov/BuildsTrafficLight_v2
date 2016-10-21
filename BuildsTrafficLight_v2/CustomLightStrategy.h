// TestLightStrategy.h

#ifndef _TESTLIGHTSTRATEGY_h
#define _TESTLIGHTSTRATEGY_h

#include "BuildsTrafficLight_v2.h"

#include "BasicLightStrategy.h"

class CustomLightStrategy : public BasicLightStrategy
{
 public:
	 void lighting();
};

#endif

