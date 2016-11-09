#include "Hour.h"

Hour::Hour(string hourStr)
{
	istringstream str(hourStr);
	char colon;
	int hour, minutes;

	str >> hour >> colon >> minutes;

	this->hour = hour;
	this->minutes = minutes;
}

int Hour::getHour() const {
	return hour;
}

int Hour::getMinutes () const {
	return minutes;
}

void Hour::setHour(int h) {
	hour = h;
}

void Hour::setMinutes(int m) {
	minutes = m;
}
