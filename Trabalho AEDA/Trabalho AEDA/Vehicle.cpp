#include "Vehicle.h"

Vehicle::Vehicle(string brand, string model, int year)
{
	this->brand = brand;
	this->model = model;
	this->year = year;
}


Vehicle::~Vehicle()
{
}

bool Vehicle::operator<(const Vehicle & v1) const
{
	if ((brand == v1.brand) && (model == v1.model)) {
		if (year > v1.year)
			return true;
		else return false;
	}
	else {
		if (brand < v1.brand) {
			if (model < v1.model)
				return true;
			else return false;
		}
		else
			return false;
	}
}
