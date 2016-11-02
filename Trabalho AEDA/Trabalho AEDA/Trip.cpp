#include "Trip.h"

Trip::Trip()
{
}


Trip::~Trip()
{
}

Trip::Trip(string driver, vector<string> stops)
{
	this->driver = driver;
	this->stops = stops;
}

int Trip::getPrice() const
{
	return stops.size(); //TODO trip price
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

int Trip::getAvailableSeats() const
{
	return availableSeats;
}