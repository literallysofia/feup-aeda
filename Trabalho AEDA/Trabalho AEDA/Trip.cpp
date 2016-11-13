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

vector<int> Trip::getPassengers() const
{
	return passengers;
}

void Trip::addPassenger(int idp)
{
	passengers.push_back(idp);
}

ostream& operator<<(ostream& out, const Trip &t) {

	out << setw(3) << t.getID();
	out << setw(5) << t.getDriver();
	out << setw(9) << t.getOrigin();
	out << setw(10) << t.getDestination();
	out << setw(5) << t.getDate();
	out << setw(5) << t.getStart();
	out << setw(5) << t.getEnd();
	out << endl; 

	return out;
}

void Trip::save(ofstream & out) const {

	out << getID() << ";"
		<< getDriver() << ";"
		<< getOrigin() << ";"
		<< getDestination() << ";"
		<< getDate() << ";"
		<< getStart() << ";"
		<< getEnd() << endl;
}