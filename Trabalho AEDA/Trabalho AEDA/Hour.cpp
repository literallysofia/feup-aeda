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

Hour::Hour(int hour, int minutes)
{
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

bool Hour::validHour()
{
	if (hour < 0 || hour > 23) return false;
	else if (minutes > 59 || minutes < 0) return false;
	return true;
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

bool Hour::operator<(const Hour &h2) const{

	if (this->hour < h2.hour) return true;
	else if (h2.hour > this->hour)return false;
	else
	{
		if (this->minutes < h2.minutes) return true;
		else return false;
	}
}

void Hour::setCurrent() {

	time_t rawtime;
	struct tm timeinfo;
	

	time(&rawtime);                   // Get the current time
	localtime_s(&timeinfo, &rawtime);  // Convert the current time to the local time

	this->setHour(timeinfo.tm_hour);
	this->setMinutes(timeinfo.tm_min);
}