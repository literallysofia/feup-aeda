#pragma once

#include <string>
#include <vector>
#include "User.h"

using namespace std;


class CandidateTrip
{
private:
	User *passanger;
	User *driver;
	float distance; //distancia desde o inicio da viagem até onde o user entra

public:
	CandidateTrip(User *u, User *d, float dist);
	User *getPassanger() const;
	User *getDriver() const;
	float getDistance() const;
	bool areBuddies() const;
	bool operator<(const CandidateTrip & ct1) const; 
};



