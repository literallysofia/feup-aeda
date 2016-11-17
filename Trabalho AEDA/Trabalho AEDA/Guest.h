#pragma once
#include <string>
#include <vector>
#include "Trip.h"

using namespace std;

class Guest
{
private:
	const string name;
	int guestID;
	string start, end;
	int numStops;
public:
	Guest();
	~Guest();
	string getName() const;
	string getStart() const;
	string getEnd() const;
	int getID() const;
	int getNumStops() const;
	void updateNumStops();
	void setNumStopsFirst();
	bool searchTrip(vector<Trip> &vec);
	//void setStart(string s) { start = s; };
	//void setEnd(string e) { end = e; };
};