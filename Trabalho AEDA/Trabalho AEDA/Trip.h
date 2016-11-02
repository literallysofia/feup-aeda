#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trip
{
private:
	int driver;
	vector<string> stops;
	vector<int> passengers;
						//bool active;
						//Date startTime;
						//Date endTime;
public:
	Trip();
	~Trip();
	Trip(int driver, vector<string> stops);
	int getDriver() const;
	vector<string> getStops() const;
	string getOrigin() const;
	string getDestination() const;
	int getPrice() const;
	//void setAvailableSeats() const;

	//bool getActive();
	//Date getStartingTime();
	//Date getEndingTime();
};