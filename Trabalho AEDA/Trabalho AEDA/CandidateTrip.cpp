#include "CandidateTrip.h"

using namespace std;


CandidateTrip::CandidateTrip(User *u, User *d, float dist)
{
	passanger = u;
	driver = d;
	distance = dist;
}

User *CandidateTrip::getPassanger() const
{
	return passanger;
}

User *CandidateTrip::getDriver() const
{
	return driver;
}

float CandidateTrip::getDistance() const {

	return distance;
}

bool CandidateTrip::areBuddies() const {

	for (int i = 0; i < driver->getBuddies().size(); i++) {
		if (driver->getBuddies().at(i) == this->passanger)
			return true;
	}

	return false;
}

bool CandidateTrip::operator<(const CandidateTrip & ct1) const
{

	if (!areBuddies() && ct1.areBuddies())
		return true;

	if (areBuddies() && !ct1.areBuddies())
		return false;

	if (!areBuddies() && !ct1.areBuddies()) {
		if (this->distance < ct1.getDistance())
			return false;
		else return true;
	}

	if (areBuddies() && ct1.areBuddies()) {
		if (this->distance < ct1.getDistance())
			return false;
		else return true;
	}

	return false;

}


