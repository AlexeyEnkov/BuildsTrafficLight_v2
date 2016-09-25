// 
// 
// 

#include "BasicLightStrategy.h"


void BasicLightStrategy::setLeds(boolean red, boolean yellow, boolean green)
{
	this->red = red;
	this->yellow = yellow;
	this->green = green;

}

void BasicLightStrategy::light() {
	TrafficLightBrightness brs = SystemConfig.getTrafficLightBrightness();
	if (red) {
		Timer1.setPwmDuty(RED_PIN, getDutyFromPercents(brs.red));
	}
	else {
		Timer1.setPwmDuty(RED_PIN, 0);
	}
	if (yellow) {
		Timer1.setPwmDuty(YELLOW_PIN, getDutyFromPercents(brs.yellow));
	}
	else {
		Timer1.setPwmDuty(YELLOW_PIN, 0);
	}
	if (green) {
		Timer1.setPwmDuty(GREEN_PIN, getDutyFromPercents(brs.green));
	}
	else {
		Timer1.setPwmDuty(GREEN_PIN, 0);
	}

}

int BasicLightStrategy::getDutyFromPercents(byte percents)
{
	long duty = percents;
	duty *= 1023;
	return duty / 100;
}
