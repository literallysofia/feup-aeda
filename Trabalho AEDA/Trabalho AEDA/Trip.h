#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trip
{
private:
	string driver;
	vector<string> stops;
	vector<int> passengers;
	int availableSeats; //TODO tipos de veiculos? nao sei quandos lugares ha e afins
						//bool active;
						//Date startTime;
						//Date endTime;
public:
	Trip();
	~Trip();
	Trip(string driver, vector<string> stops);
	int getPrice() const;
	vector<string> getStops() const;
	string getOrigin() const;
	string getDestination() const;
	int getAvailableSeats() const;
	//void setAvailableSeats() const;

	//bool getActive();
	//Date getStartingTime();
	//Date getEndingTime();
};