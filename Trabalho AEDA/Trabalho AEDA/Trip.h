#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trip
{
private:
	int driver;
	int ID;
	vector<string> stops;
	vector<int> passengers;
	int seatsAvailable;
						//bool active;
						//Date startTime;
						//Date endTime;
public:
	Trip();
	~Trip();
	Trip(int driver, vector<string> stops);
	int getDriver() const;
	int getID() const;
	vector<string> getStops() const;
	string getOrigin() const;
	string getDestination() const;
	int getPrice() const;
	void setDriverID(int driverID);
	void setID(int id);
	void setStops(vector<string> &vec);
	void addPassenger(int passengerID);
	vector<int> getPassengers() const;
	void setAvailableSeats(int num);
	int getNumSeats() const;

	//bool getActive();
	//Date getStartingTime();
	//Date getEndingTime();
};