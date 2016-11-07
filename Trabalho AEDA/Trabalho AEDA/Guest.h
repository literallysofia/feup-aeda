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
	int currentTrip;
public:
	Guest();
	~Guest();
	string getName() const;
	string getStart() const;
	string getEnd() const;
	int getID() const;
	bool searchTrip(vector<Trip> &vec);
	//void setStart(string s) { start = s; };
	//void setEnd(string e) { end = e; };
};