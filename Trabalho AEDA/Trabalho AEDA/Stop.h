#pragma once
#include <string>
#include <vector>
using namespace std;

class Stop
{
private:
	string code;
	int availableSeats;
	vector<int> passengers;
public:
	Stop();
	Stop(string code, int seats);
	~Stop();
	string getCode() const;
	int getAvailableSeats() const;
	vector<int> getPassengers() const;
	void decAvailableSeats();
	void addPassenger(int id);
};