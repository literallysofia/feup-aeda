#pragma once
#include "User.h"
#include <string>
using namespace std;

class Stop
{
private:
	string location;
	int availableSeats;
	vector<User *> Passengers;
public:
	Stop();
	~Stop();
	string getLocation() const;
	int getAvailableSeats() const;
	vector<User *> getPassengers() const;
	//void setAvailableSeats();
};

