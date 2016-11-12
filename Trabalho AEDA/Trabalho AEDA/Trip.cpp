#include "Trip.h"

int Trip::counter = 1;

Trip::Trip()
{
}

Trip::Trip(int ID, int driver, vector<Stop> stops, Date date, Hour start, Hour end)
{
	this->ID = ID;
	this->driver = driver;
	this->stops = stops;
	this->date = date;
	this->startTime = start;
	this->endTime = end;
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

vector<Stop> Trip::getStops() const
{
	return stops;
}

Date Trip::getDate() const
{
	return date;
}

Hour Trip::getStart() const
{
	return startTime;
}

Hour Trip::getEnd() const
{
	return endTime;
}

string Trip::getOrigin() const
{
	return stops.at(0).getCode();
}

string Trip::getDestination() const
{
	return stops.at(stops.size() - 1).getCode();
}