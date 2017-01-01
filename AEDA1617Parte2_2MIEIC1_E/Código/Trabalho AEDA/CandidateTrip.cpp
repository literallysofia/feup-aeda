#include "CandidateTrip.h"

using namespace std;


CandidateTrip::CandidateTrip(User *u, User *d, float dist, string IS, string ES)
{
	passanger = u;
	driver = d;
	distance = dist;
	initStop = IS;
	endStop = ES;
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

string CandidateTrip::getInitStop() const
{
	return initStop;
}

string CandidateTrip::getEndStop() const
{
	return endStop;
}

bool CandidateTrip::areBuddies() const {

	for (unsigned int i = 0; i < driver->getBuddies().size(); i++) {
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
		if (this->distance > ct1.getDistance())
			return true;
		else return false;
	}
	
	if (areBuddies() && ct1.areBuddies()) {
		if (this->distance > ct1.getDistance())
			return true;
		else return false;
	}

	return false;

}


