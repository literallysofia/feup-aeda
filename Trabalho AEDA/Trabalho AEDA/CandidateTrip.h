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
	string initStop;
	string endStop;

public:
	CandidateTrip(User *u, User *d, float dist, string IS, string ES);
	User *getPassanger() const;
	User *getDriver() const;
	float getDistance() const;
	string getInitStop() const;
	string getEndStop() const;
	bool areBuddies() const;
	bool operator<(const CandidateTrip & ct1) const; 
};



