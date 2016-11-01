#pragma once
#include "User.h"
class Passenger :
	public User
{
	unsigned int numTrips;
	string beginning, end;			//nomes das paragens finais e iniciais
									//podem ser sempre as mesmas ou alteradas pelo utilizador no programa

public:
	Passenger(string name, string password);
	~Passenger();
	inline bool ownCar() const { return false; };
	void resetTrips(void) { numTrips = 0; };
	void addTrip(void) { numTrips++; };
	string getBeginning() const { return beginning; };
	string getEnd() const { return end; };
	float payment() const;
}; 

