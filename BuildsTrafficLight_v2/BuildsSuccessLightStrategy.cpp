// 
// 
// 

#include "BuildsSuccessLightStrategy.h"


BuildsSuccessLightStrategy::BuildsSuccessLightStrategy()
{
	setLeds(false, false, true);
}

void BuildsSuccessLightStrategy::lighting() {
	light();
}