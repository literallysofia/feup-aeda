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

	bool operator<(const Vehicle& v1) const;
	//bool operator==(const Vehicle& v1) const;
};

