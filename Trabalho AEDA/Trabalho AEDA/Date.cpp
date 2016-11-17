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

Date::Date(int day, int month, int year)
{
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

string Date::toString() {

	string date_s;

	if (day < 10 && month < 10)
		date_s = '0' + day + '/' + '0' + month  + '/' + year;
	else if (day < 10)
		date_s = '0' + day + '/' + month + '/' + year;
	else if (month < 10)
		date_s = day + '/' + "0" + month + '/' + year;
	else date_s = day + '/' + month + '/' + year;

	return date_s;

}


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

	if (year/2000 < 1) return false;
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

int Date::daysBetween(Date &d2)
{
	int month_days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	int days = 0;

	if (this->year == d2.year)
	{
		if (this->month == d2.month)
			days = d2.day - this->day;
		else
		{
			for (int i = this->month; i < d2.month - 1; i++)
				days += month_days[i];
			days += month_days[this->month - 1] - this->day + d2.day;
		}
	}
	else
	{
		for (int i = 0; i < d2.month - 1; i++)
			days += month_days[i];
		for (int i = this->month; i < 12; i++)
			days += month_days[i];
		if (d2.year - this->year >= 0)
			days += (d2.year - this->year - 1) * 365 +
			month_days[this->month - 1] - this->day + d2.day;
	}	

	return days;
}

void Date::setCurrent() {

	//recolha de informacao da data atual
	char date[9];
	_strdate_s(date);
	string nova_data_string = date;					//reformulaçao pois a data é recebida de forma americana mm/dd/yy
	int dia = atoi(nova_data_string.substr(3, 2).c_str());
	int mes = atoi(nova_data_string.substr(0, 2).c_str());
	int ano = atoi(nova_data_string.substr(6, 2).c_str()) + 2000;

	this->setDay(dia); this->setMonth(mes); this->setYear(ano);

	///////////////
}