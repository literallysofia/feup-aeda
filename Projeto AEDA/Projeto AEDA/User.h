#pragma once

#include "Agency.h"
#include <string>

using namespace std;

class User
{
	const string name;
	const unsigned int ID;
	string password;
	vector <User *> buddies;

public:
	User(string name, string password);
	~User();
	void addBuddy(User * user) { buddies.push_back(user); }
	string getName() const { return name; };
	unsigned int getID() const { return ID; };
	string getPassword() const { return password; };
	vector<User *> getBuddies() const { return buddies; };
	virtual bool ownCar() const{};
	virtual float payment() const{};
	virtual void resetTrips() {};
};

