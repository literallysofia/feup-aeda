#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Date {
private:
	int day;
	int month;
	int year;

public:
	Date() {};
	Date(string date); // data na forma DD/MM/AAAA
	Date(int day, int month, int year);

	int getDay() const;
	int getMonth() const;
	int getYear() const;
	void setDay(int day);
	void setMonth(int month);
	void setYear(int yaer);
	

	friend ostream& operator<<(ostream& out, Date& date); 
	string toString();
	friend bool operator< (Date & d1, Date& d2);
	friend bool operator> (Date& d1, Date& d2);
	friend bool operator== (Date& d1, Date& d2); 
	bool valid() const;
	int daysBetween(Date &other);
	void setCurrent();
};