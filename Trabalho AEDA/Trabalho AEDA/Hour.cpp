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

ostream& operator<<(ostream& out, Hour &h) {

	if (h.hour < 10 && h.minutes < 10)
		out << "0" << h.hour << ':' << "0" << h.minutes;
	else if (h.hour < 10)
		out << "0" << h.hour << ':'<< h.minutes;
	else if (h.minutes < 10)
		out << h.hour << ':' << "0" << h.minutes;
	else out << h.hour << ':' << h.minutes;

	return out;
}