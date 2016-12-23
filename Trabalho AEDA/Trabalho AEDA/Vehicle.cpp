#include "Vehicle.h"

Vehicle::Vehicle(string brand, string model, int year, User *driver)
{
	this->brand = brand;
	this->model = model;
	this->year = year;
	this->driver = driver;
}


Vehicle::~Vehicle()
{
}

string Vehicle::getBrand() const
{
	return brand;
}

string Vehicle::getModel() const
{
	return model;
}

int Vehicle::getYear() const
{
	return year;
}

User * Vehicle::getUser() const
{
	return driver;
}

void Vehicle::setUser(User * d1)
{
	driver = d1;
}

bool Vehicle::operator<(const Vehicle & v1) const
{
	if ((brand == v1.brand) && (model == v1.model) && (year == v1.year)) {
		if (driver->getID() < v1.driver->getID())
			return true;
		else return false;
	}
	else {
		if ((brand == v1.brand) && (model == v1.model)) {
			if (year > v1.year)
				return true;
			else return false;
		}
		else {
			if (brand == v1.brand) {
				if (model < v1.model)
					return true;
				else return false;
			}
			else {
				if (brand < v1.brand)
					return true;
				else return false;
			}
		}
	}
}
