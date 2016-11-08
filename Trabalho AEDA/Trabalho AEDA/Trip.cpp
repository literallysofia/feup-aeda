#include "Trip.h"

int Trip::counter = 0;

Trip::Trip()
{
}

Trip::Trip(int driver, vector<string> stops)
{
	ID = counter++;
	this->driver = driver;
	this->stops = stops;
}

Trip::~Trip()
{
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

void Trip::addPassenger(int passengerID)
{
	passengers.push_back(passengerID);
}

vector<int> Trip::getPassengers() const
{
	return passengers;
}

void Trip::setAvailableSeats(int num)
{
	seatsAvailable = num;
}

int Trip::getNumSeats() const
{
	return seatsAvailable;
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