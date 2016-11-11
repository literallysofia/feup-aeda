#include "Date.h"

Date::Date(string dateStr)
{
	istringstream str(dateStr);
	char backlash1, backlash2;
	int day, month, year;

	str >> day >> backlash1 >> month >> backlash2 >> year;

	this->day = day;
	this->month = month;
	this->year = year;
}

int Date::getDay() const {
	return day;
}

int Date::getMonth() const {
	return month;
}

int Date::getYear() const {
	return year;
}

void Date::setDay(int d) {
	day = d;
}

void Date::setMonth(int m) {
	month = m;
}

void Date::setYear(int a) {
	year = a;
}

ostream& operator<<(ostream& out, Date & date) {

	if (date.day < 10 && date.month < 10)
		out 
		//<< setw(19) 
		<< "0" << date.day << '/' << "0" << date.month << '/' << date.year;
	else if (date.day < 10)
		out 
		//<< setw(19) 
		<< "0" << date.day << '/' << date.month << '/' << date.year;
	else if (date.month < 10)
		out 
		//<< setw(20) 
		<< date.day << '/' << "0" << date.month << '/' << date.year;
	else out 
		//<< setw(20) 
		<< date.day << '/' << date.month << '/' << date.year;
	
	return out;
}

/*
string toString(Date & date) {

	string date_s;

	if (date.day < 10 && date.month < 10)
		date_s = '0' + date.day + '/' + '0' + date.month  + '/' + date.year;
	else if (date.day < 10)
		date_s = '0' + date.day + '/' + date.month + '/' + date.year;
	else if (date.month < 10)
		date_s = date.day + '/' + "0" + date.month + '/' + date.year;
	else date_s = date.day + '/' + date.month + '/' + date.year;

	return date_s;

}
*/

bool operator< (Date& d1, Date& d2) {
	if (!d1.valid()) { return false; };
	if (!d2.valid()) { return false; };
	if (d1.getYear()<d2.getYear()) { return true; }
	else if (d1.getYear()>d2.getYear()) { return false; }
	else
	{ // mesmo ano
		if (d1.getMonth()<d2.getMonth()) { return true; }
		else if (d1.getMonth()>d2.getMonth()) { return false; }
		else
		{ // mesmo mes
			if (d1.getDay()<d2.getDay()) { return true; }
			else { return false; }
		};
	};
	return false;
};

bool operator== (Date& d1, Date& d2) {
	// verifica se 2 datas sao iguais
	if (!d1.valid()) { return false; };
	if (!d2.valid()) { return false; };
	if ((d1.getDay() == d2.getDay())
		&& (d1.getMonth() == d2.getMonth())
		&& (d1.getYear() == d2.getYear())) {
		return true;
	};
	return false;
}

bool operator > (Date& d1, Date& d2) {
	if (d1 == d2) { return false; };
	if (d1<d2) { return false; };
	return true;
}

bool Date::valid() const {

	if (year < 0) return false;
	if (month >12 || month <1) return false;
	if (day >31 || day <1) return false;
	if ((day == 31 &&
		(month == 2 || month == 4 || month == 6 || month == 9 || month == 11)))
		return false;
	if (day == 30 && month == 2) return false;
	if (year <2000) {
		if ((day == 29 && month == 2) && !((year - 1900) % 4 == 0)) return false;
	};
	if (year >2000) {
		if ((day == 29 && month == 2) && !((year - 2000) % 4 == 0)) return false;
	};

	return true;
};