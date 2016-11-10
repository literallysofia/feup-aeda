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
	Date(string date); // data na forma DD/MM/AAA

	int getDay() const;
	int getMonth() const;
	int getYear() const;
	void setDay(int day);
	void setMonth(int month);
	void setYear(int yaer);
	

	friend ostream& operator<<(ostream& out, Date& date); 
	friend bool operator< (Date & d1, Date& d2);
	friend bool operator> (Date& d1, Date& d2);
	friend bool operator== (Date& d1, Date& d2); 
	bool valid() const;
	//friend bool operator>= (Date& d1, Date& d2); // operador de comparacao (maior ou igual)	
	//friend bool operator!= (Date& d1, Date& d2); // operador de desigualdade
	//friend bool validade2datas(Date& d1, Date& d2);
	// verifica a validade das datas fornecidas
	// @param d1 - primeira data
	// @param d2 - segunda data	
	// @return bool - true se ambas as datas sao validas, ou false, em caso contrario
	// verifica se a data e valida
	// @return bool - true se a data for valida, false caso contrario
};