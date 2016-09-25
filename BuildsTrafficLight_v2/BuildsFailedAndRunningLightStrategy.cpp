// 
// 
// 

#include "BuildsFailedAndRunningLightStrategy.h"

BuildsFailedAndRunningLightStrategy::BuildsFailedAndRunningLightStrategy()
{
	setLeds(true, true, false);
}

void BuildsFailedAndRunningLightStrategy::lighting() {
	light();
}
