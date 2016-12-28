#include "Trip.h"

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

void Trip::setDriver(int id)
{
	driver = id;
}

void Trip::setDate(Date d)
{
	this->date = d;
}

void Trip::setStops(int pos, int userID)
{
	for (unsigned int i = 0; i < stops.size(); i++) {
		if (pos == i) {
			stops.at(i).decAvailableSeats();
			stops.at(i).addPassenger(userID);
		}
	}
	return;
}

ostream& operator<<(ostream& out, const Trip &t) {

	out << setw(3) << t.getID();
	out << setw(5) << t.getDriver();
	out << setw(9) << t.getOrigin();
	out << setw(10) << t.getDestination();

	if (t.getDate().getDay() < 10)
		out << setw(4) << t.getDate();
	else out << setw(5) << t.getDate();

	if (t.getStart().getHour() < 10)
		out << setw(4) << t.getStart();
	else out << setw(5) << t.getStart();

	if (t.getEnd().getHour() < 10)
		out << setw(4) << t.getEnd();
	else out << setw(5) << t.getEnd();
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

void Trip::saveAT(ofstream & out) const {

	out << getID() << ";"
		<< getDriver() << ";[";


	for (unsigned int i = 0; i < stops.size(); i++) {

		if (i != 0)
			out << ";";

		out << stops[i].getCode() << "," << stops[i].getAvailableSeats() << ",(";


		if (stops[i].getPassengers().size() != 0)
		{

			for (unsigned int j = 0; j < stops[i].getPassengers().size(); j++) {

				if (j != 0)
					out << ",";
				out << stops[i].getPassengers()[j];
			}
		}

		out << ")";
	}
	out << "];"
		<< getDate() << ";"
		<< getStart() << ";"
		<< getEnd() << endl;
}

bool Trip::operator ==(const Trip t) const {
	if (this->ID == t.ID || this->driver == t.driver)
		return true;
	else
		return false;
}

priority_queue<CandidateTrip> Trip::getCandidateQueue() const
{
	return candidateQueue;
}

void Trip::addCandidate(CandidateTrip ct)
{
	candidateQueue.push(ct);
}