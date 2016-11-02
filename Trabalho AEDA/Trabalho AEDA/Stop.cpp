#include "Stop.h"

Stop::Stop()
{
}

Stop::~Stop()
{
}

string Stop::getLocation() const
{
	return location;
}

int Stop::getAvailableSeats() const
{
	return availableSeats;
}

vector<User*> Stop::getPassengers() const
{
	return Passengers;
}
