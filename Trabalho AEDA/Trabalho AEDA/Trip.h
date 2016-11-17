#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Stop.h"
#include "Date.h"
#include "Hour.h"
using namespace std;

class Trip
{
private:
	static int counter;
	int ID;
	int driver;
	vector<Stop> stops;
	Date date;
	Hour startTime;
	Hour endTime;
	//int carSeats;
	//bool active;
public:
	Trip();
	Trip(int ID, int driver, vector<Stop> stops, Date date, Hour start, Hour end);
	~Trip();
	int getDriver() const;
	int getID() const;
	vector<Stop> getStops() const;
	Date getDate() const;
	Hour getStart() const;
	Hour getEnd() const;
	string getOrigin() const;
	string getDestination() const;
	void setDriver(int id);
	void setDate(Date d);
	void setStops(int pos, int userID);
	void save(ofstream & out) const;
	void saveAT(ofstream & out) const;
	friend ostream& operator<<(ostream& out, const Trip &t);
	bool operator ==(const Trip t) const;
};