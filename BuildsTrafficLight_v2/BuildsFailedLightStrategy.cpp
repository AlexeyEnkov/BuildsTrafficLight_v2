// 
// 
// 

#include "BuildsFailedLightStrategy.h"


BuildsFailedLightStrategy::BuildsFailedLightStrategy()
{
	setLeds(true, false, false);
}

void BuildsFailedLightStrategy::lighting() {
	light();
}