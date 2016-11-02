#include "Trip.h"

Trip::Trip()
{
}


Trip::~Trip()
{
}

Trip::Trip(int driver, vector<string> stops)
{
	this->driver = driver;
	this->stops = stops;
}

int Trip::getDriver() const
{
	return driver;
}

int Trip::getID() const
{
	return ID;
}

int Trip::getPrice() const
{
	return (int)stops.size(); //TODO trip price
}

void Trip::setDriverID(int driverID)
{
	driver = driverID;
}

void Trip::setID(int id)
{
	ID = id;
}

void Trip::setStops(vector<string>& vec)
{
	stops = vec;
}

vector<string> Trip::getStops() const
{
	return stops;
}

string Trip::getOrigin() const
{
	return stops.at(0);
}

string Trip::getDestination() const
{
	return stops.at(stops.size() - 1);
}