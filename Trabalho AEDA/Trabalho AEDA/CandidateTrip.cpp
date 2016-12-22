#include "CandidateTrip.h"

using namespace std;


CandidateTrip::CandidateTrip(User *u, User *d, float dist)
{
	passanger = u;
	driver = d;
	distance = dist;
}

User *CandidateTrip::getPassanger()
{
	return passanger;
}

User *CandidateTrip::getDriver()
{
	return driver;
}

float CandidateTrip::getDistance() {

	return distance;
}

bool CandidateTrip::areBuddies() {

	for (int i=0; i < driver->getBuddies().size(); i++) {
		if (driver->getBuddies().at(i) == this->passanger)
			return true;
	}

	return false;
}

bool CandidateTrip::operator<(CandidateTrip & ct1)
{
	if (areBuddies() && !ct1.areBuddies())
		return true;

	if (!areBuddies() && ct1.areBuddies())
		return false;

	if (areBuddies() && ct1.areBuddies() || !areBuddies() && !ct1.areBuddies()) {
		if (this->distance < ct1.getDistance())
			return true;
		else return false;
	}

	return false;

}


