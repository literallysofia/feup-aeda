#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

class Hour {
private:
	int hour;
	int minutes;
public:
	Hour() {};
	Hour(string hour);
	Hour(int hour, int minutes);
	int getHour() const;
	int getMinutes() const;
	void setHour(int hour);
	void setMinutes(int mimnutes);
	friend ostream& operator<<(ostream& out, Hour& hour);
	bool validHour();
	bool operator<(const Hour &h2) const;
	void setCurrent();
};