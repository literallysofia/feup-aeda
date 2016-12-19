#pragma once
#include <string>

using namespace std;

class Vehicle
{
private:
	string brand;
	string model;
	int year;
public:
	Vehicle(string brand, string model, int year);
	~Vehicle();

	bool operator<(const Vehicle& v1) const;
	//bool operator==(const Vehicle& v1) const;
};

