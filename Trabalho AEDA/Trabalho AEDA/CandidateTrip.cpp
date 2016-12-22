#include "CandidateTrip.h"

CandidateTrip::CandidateTrip(User * u, User * d, float dist)
{
	user = u;
	driver = d;
	distance = dist;
}

User * CandidateTrip::getUser()
{
	return user;
}

User * CandidateTrip::getDriver()
{
	return driver;
}

float CandidateTrip::getDistance() {

	return distance;
}

bool CandidateTrip::areBuddies() {

	for (int i; i < this->driver->getBuddies().size(); i++) {
		if (this->driver->getBuddies().at(i) == this->user)
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


