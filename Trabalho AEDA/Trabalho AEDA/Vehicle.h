#pragma once
#include "User.h"
#include <string>

using namespace std;

class Vehicle
{
private:
	string brand;
	string model;
	int year;
	User *driver;
public:
	Vehicle(string brand, string model, int year, User *driver);
	~Vehicle();

	string getBrand() const;
	string getModel() const;
	int getYear() const;
	User* getUser() const;
	void setUser(User* d1);
	bool operator<(const Vehicle& v1) const;

	friend ostream& operator<<(ostream& os, const Vehicle& v1) {
		os << v1.brand << ";" << v1.model << ";" << v1.year << ";" << v1.driver->getName();
		return os;
	}

	//bool operator==(const Vehicle& v1) const;
};

