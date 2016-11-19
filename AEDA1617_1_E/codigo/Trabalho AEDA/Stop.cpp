#include "Stop.h"

Stop::Stop()
{
}

Stop::~Stop()
{
}

Stop::Stop(string code, int seats)
{
	this->code = code;
	availableSeats = seats;
}

Stop::Stop(string code, int seats, vector<int> vpass)
{
	this->code = code;
	availableSeats = seats;
	passengers = vpass;
}

string Stop::getCode() const
{
	return code;
}

int Stop::getAvailableSeats() const
{
	return availableSeats;
}

vector<int> Stop::getPassengers() const
{
	return passengers;
}

void Stop::decAvailableSeats()
{
	availableSeats--;
}

void Stop::addPassenger(int id)
{
	passengers.push_back(id);
}
